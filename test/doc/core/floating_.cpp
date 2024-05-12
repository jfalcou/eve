#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_8t = eve::wide<std::int8_t, eve::fixed<4>>;
using wide_64t = eve::wide<std::uint64_t, eve::fixed<4>>;

int main()
{
  wide_8t p8 = {-1, -3, 6, 127};
  wide_64t p64 = {1, 2, 100, eve::valmax(eve::as<std::int64_t>())};

  std::cout << "---- simd" << '\n'
            << "<- p8                         = " << p8 << '\n'
            << "-> floating_(p8)              = " << eve::floating_(p8) << '\n'
            << "<- p64                        = " << p64 << '\n'
            << "-> floating_(p64)             = " << eve::floating_(p64) << '\n';
  return 0;
}
