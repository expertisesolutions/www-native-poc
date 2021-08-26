
#include <www-native/test.hpp>
#include <beast_http.hpp>

struct controller
{
  handler
  <
    void,
    get,
    path<"cats/:id">
  >
  foo(param<int, "id"> id)
  {
    std::cout << "foo::id " << id << std::endl;
    return {};
  }
};


template <typename T, typename L, typename U, typename...Args, typename Body = http::string_body>
void bar(L listener, U(T::* f)(Args...))
{
  listener->handler = 
    []
    (http::request<Body> req,
     std::function<void(http::response<Body>)> send)
  {
    std::cout << "handler for type " << typeid(U(Args...)).name() << std::endl;
    parse_path<U> (req);
  };
}


int main(int argc, const char** argv)
{
  // Check command line arguments.
  if (argc == 2 && !strcmp(argv[1], "-h"))
  {
    std::cerr <<
      "Usage: http-server-async <address> <port> <doc_root> <threads>\n" <<
      "Example:\n" <<
      "    http-server-async [0.0.0.0] [8080]\n";
    return EXIT_FAILURE;
  }
  auto address = net::ip::make_address("0.0.0.0");
  if (argc >= 2)
    address = net::ip::make_address(argv[1]);
  unsigned short port = 8080;
  if (argc >= 3)
    port = static_cast<unsigned short>(std::atoi(argv[2]));
  //auto const doc_root = std::make_shared<std::string>(argv[3]);
  //auto const threads = std::max<int>(1, std::atoi(argv[4]));
  auto const threads = 1;

  // The io_context is required for all I/O
  net::io_context ioc{threads};

  // Create and launch a listening port
  auto const listener = std::make_shared<struct listener>(
        ioc,
        tcp::endpoint{address, port}
        /*, doc_root*/);
  listener->run();

  // Run the I/O service on the requested number of threads
  std::vector<std::thread> v;
  v.reserve(threads - 1);
  for(auto i = threads - 1; i > 0; --i)
    v.emplace_back(
        [&ioc]
        {
            ioc.run();
        });

  bar<controller>
    (
     listener
     , &controller::foo
    );


    ioc.run();
}

