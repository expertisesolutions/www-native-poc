

template <typename Path, typename Operation, typename Value>
constexpr auto fold_path (Path path, Operation operation, Value value, std::size_t const index = 0u)
{
  if constexpr (sizeof(Path::path_literal.value) - 1 == index)
    return value;
  else
    return fold_path (path, operation, operation (Path::path_literal.value[index], value), index+1);
}

