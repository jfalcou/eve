#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_16t = eve::wide<std::uint16_t, eve::fixed<4>>;

int main()
{
  wide_16t p16 = {1, 2, 100, eve::valmax(eve::as<std::int8_t>())};

  std::cout << "---- simd" << '\n'
            << "<- p16                     = " << p16 << '\n'
            << "-> upgrade(p16)            = " << eve::upgrade(p16) << '\n'
            << "-> inc(p16)                = " << eve::inc(p16)     << '\n'
            << "-> inc(upgrade(p16))       = " << eve::inc(eve::upgrade(p16)) << '\n';
  return 0;
}
