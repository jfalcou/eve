
#include <eve/wide.hpp>
#include <iostream>
#include <eve/module/core.hpp>

using wide_it = eve::wide<std::uint64_t, eve::fixed<8>>;

int main()
{
  wide_it pi = {1, 2, 3, 4, 5, 6, 7, 8};
  auto _0 = std::integral_constant<size_t, 0>();
  auto _1 = std::integral_constant<size_t, 1>();
  auto _2 = std::integral_constant<size_t, 2>();
  auto _3 = std::integral_constant<size_t, 3>();
  auto _4 = std::integral_constant<size_t, 4>();

  std::cout << "---- simd" << '\n'
            << "<- pi              = " << pi << '\n'
            << "-> reverse(pi)     = " << eve::reverse(pi) << '\n'
            << "-> reverse(pi, _0) = " << eve::reverse(pi, _0) << '\n'
            << "-> reverse(pi, _1) = " << eve::reverse(pi, _1) << '\n'
            << "-> reverse(pi, _2) = " << eve::reverse(pi, _2) << '\n'
            << "-> reverse(pi, _3) = " << eve::reverse(pi, _3) << '\n'
            << "-> reverse(pi, _4) = " << eve::reverse(pi, _4) << '\n'
;

  std::uint64_t xf = 0xf0ff0fff0ffff00ULL;

  std::cout << "---- scalar" << '\n'
            << "<- xf          = " << std::hex << "0x" << xf << '\n'
            << "-> reverse(xf) = " << std::hex << "0x" << eve::reverse(xf) << '\n';

}
