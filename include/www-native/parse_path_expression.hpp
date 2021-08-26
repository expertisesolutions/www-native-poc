
#include <www-native/string_literal.hpp>
#include <www-native/fold.hpp>

template <string_literal String>
struct static_string
{
  constexpr auto static string = String;
};

template <string_literal Id>
struct parameter
{
  constexpr auto static id = Id;
};

// template <typename Tuple>
// struct tuple_holder;

// template <typename...Args>
// struct tuple_holder<std::tuple<Args...>>
// {
//   constexpr tuple_holder(std::tuple<Args...> other) : tuple(other) {}
//   std::tuple<Args...> tuple;
// };

// template <class T> struct explode;

// template <class... ArgTypes, template <ArgTypes... Args> class T, ArgTypes... N>
// struct explode<T<N...>>
// {
//     typedef T<N...> type;
//     template <ArgTypes... Args> using template_ = T<Args...>;
//     template <int I> using type_of_parameter =
//         typename std::tuple_element<I, std::tuple<ArgTypes...>>::type;
//     template <int I> struct nontype_parameter {
//         static constexpr type_of_parameter<I> value() {
//             return std::get<I>(std::tuple<ArgTypes...>(N...));
//         }
//     };
// };


// template <>
// struct tuple_holder<std::tuple<>>
// {
//   constexpr tuple_holder(std::tuple<> other) {}
//   std::tuple<> tuple;
// };

struct parse_path_operation
{
  template <typename Tuple>
  constexpr auto operator()(char c, Tuple&& tuple)
  {
    return std::true_type{};
  };
};

template <typename HandlerInfo/*, typename T*/>
constexpr auto parse_path_expression(/*T const& object*/)
{
  return fold_path
    (typename HandlerInfo::path{}
     , parse_path_operation{}
    // , [](auto character, auto value) constexpr
    // {
    //   // start of a parameter
    //   if (character == ':')
    //   {
    //     return std::tuple<parameter<"">>{}; //std::tuple_cat(value, std::tuple<parameter<"">>{});
    //   }
    //   // else if (std::tuple_size_v<decltype(value)> == 0)
    //   // {
    //   //   return std::tuple_cat(value, std::tuple<static_string<"">>{});       
    //   // }
    //   else
    //     return value;
    // }
     , std::tuple<>{});
}


