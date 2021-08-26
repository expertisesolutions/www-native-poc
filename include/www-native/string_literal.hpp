
#ifndef WWW_NATIVE_STRING_LITERAL_HPP
#define WWW_NATIVE_STRING_LITERAL_HPP

template <std::size_t N>
struct string_literal
{
  constexpr string_literal(const char(&str)[N])
  {
    std::copy_n(str, N, value);
  }
  template <std::size_t A1, std::size_t A2>
  constexpr string_literal(const char(&str1)[A1], const char(&str2)[A2])
  {
    static_assert (A1 + A2 == N);
    std::copy_n(str1, A1, value);
    std::copy_n(str2, A2, value + A1);
  }
  char value[N];
};

template <std::size_t A1, std::size_t A2>
constexpr auto concat(string_literal<A1> a1, string_literal<A2> a2)
{
  return string_literal<A1+A2>(a1, a2);
}

#endif
