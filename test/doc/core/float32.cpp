#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_64t = eve::wide<std::uint64_t, eve::fixed<4>>;
using wide_8t = eve::wide<std::uint8_t, eve::fixed<4>>;

int main()
{
  wide_64t p64 = {1, 2, 100, eve::valmax(eve::as<std::int64_t>())};

  std::cout << "---- simd" << '\n'
            << "<- p64                      = " << p64 << '\n'
            << "-> float32(p64)             = " << eve::float32(p64) << '\n';
  return 0;
}
