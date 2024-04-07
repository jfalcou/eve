#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_32t = eve::wide<std::uint32_t, eve::fixed<4>>;

int main()
{
  wide_32t p32 = {1, 2, 100, eve::valmax(eve::as<std::int32_t>())};

  std::cout << "---- simd" << '\n'
            << "<- p32                      = " << p32 << '\n'
            << "-> upgrade_(p32)             = " << eve::upgrade_(p32) << '\n';
  return 0;
}
