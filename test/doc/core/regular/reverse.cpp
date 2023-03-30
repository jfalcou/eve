
#include <eve/wide.hpp>
#include <iostream>
#include <eve/module/core.hpp>

using wide_it = eve::wide<std::uint64_t, eve::fixed<8>>;

int main()
{
  wide_it pi = {1, 2, 3, 4, 5, 6, 7, 8};

  std::cout << "---- simd" << '\n'
            << "<- pi                                               = " << pi << '\n'
            << "-> reverse(pi)                                      = " << eve::reverse(pi) << '\n'
            << "-> reverse(pi, std::integral_constant<size_t, 0>{}) = " << eve::reverse(pi, std::integral_constant<size_t, 0>{} ) << '\n'
            << "-> reverse(pi, std::integral_constant<size_t, 1>{}) = " << eve::reverse(pi, std::integral_constant<size_t, 1>{} ) << '\n'
            << "-> reverse(pi, std::integral_constant<size_t, 2>{}) = " << eve::reverse(pi, std::integral_constant<size_t, 2>{} ) << '\n'
            << "-> reverse(pi, std::integral_constant<size_t, 3>{}) = " << eve::reverse(pi, std::integral_constant<size_t, 3>{} ) << '\n'
            << "-> reverse(pi, std::integral_constant<size_t, 4>{}) = " << eve::reverse(pi, std::integral_constant<size_t, 4>{} ) << '\n'
;

  std::uint64_t xf = 0xf0ff0fff0ffff00ULL;

  std::cout << "---- scalar" << '\n'
            << "<- xf          = " << std::hex << "0x" << xf << '\n'
            << "-> reverse(xf) = " << std::hex << "0x" << eve::reverse(xf) << '\n';

}
