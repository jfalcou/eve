
#include <eve/wide.hpp>
#include <iostream>
#include <eve/module/core.hpp>

using wide_it = eve::wide<std::uint64_t, eve::fixed<8>>;

int main()
{
  wide_it pi = {1, 2, 3, 4, 5, 6, 7, 8};

  std::cout << "---- simd" << '\n'
            << "<- pi              = " << pi << '\n'
            << "-> reverse(pi)     = " << eve::reverse(pi) << '\n'
;

  std::uint64_t xf = 0xf0ff0fff0ffff00ULL;

  std::cout << "---- scalar" << '\n'
            << "<- xf          = " << std::hex << "0x" << xf << '\n'
            << "-> reverse(xf) = " << std::hex << "0x" << eve::reverse(xf) << '\n';

}
