
#include <algorithm>
#include <cstdlib>
#include <tuple>
#include <iostream>

#include <www-native/parse_path_expression.hpp>
#include <www-native/string_literal.hpp>

template <typename R, typename...Args>
struct handler
{
  typedef typename std::tuple_element<1, std::tuple<Args...>>::type path;
};

template <typename X, string_literal ParamName = "">
struct param
{
  constexpr param(X value) : value(value) {}  
  constexpr operator X() const { return X{}; }

  X value;
};

struct get;
struct post;
template <string_literal PathLiteral>
struct path
{
  constexpr auto static path_literal = PathLiteral;
};

template <typename HandlerInfo, typename T>
constexpr void parse_path (T&& object)
{
  static_assert(HandlerInfo::path::path_literal.value[0] == 'c');

  constexpr auto path_expression = parse_path_expression<HandlerInfo>(/*object*/);
  std::cout << typeid(path_expression).name() << std::endl;
  //parse_element();
}

