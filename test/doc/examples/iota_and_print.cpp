#include <iostream>
#include <memory>
#include <numeric>

#include <eve/wide.hpp>

//! [iota-print]
template <typename T>
void iota_and_print()
{
  // The number of elements will be deduced automatically according to the
  // target architecture selected
  using wide_t = eve::wide<T>;

  // Allocates aligned memory using expected alignment
  std::unique_ptr<T[]> data(new T[wide_t::static_size * sizeof(T)]);
  std::iota(data.get(), data.get() + wide_t::static_size, T(1));

  // Constructs a wide (which will call `eve::aligned_load<wide_t>` to
  // fill up its data)
  wide_t p{data.get()};

  // Now just print the loaded data
  std::cout << p << std::endl;
}

int main()
{
  iota_and_print<std::int8_t>();
  iota_and_print<std::uint8_t>();
  // --
  iota_and_print<std::int16_t>();
  iota_and_print<std::uint16_t>();
  // --
  iota_and_print<std::int32_t>();
  iota_and_print<std::uint32_t>();
  // --
  iota_and_print<std::int64_t>();
  iota_and_print<std::uint64_t>();
  // --
  iota_and_print<float>();
  // --
  iota_and_print<double>();
  return 0;
}
//! [iota-print]
