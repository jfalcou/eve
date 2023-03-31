
#include <eve/wide.hpp>
#include <iostream>
#include <eve/module/core.hpp>

using wide_it = eve::wide<std::uint64_t, eve::fixed<8>>;

int main()
{
  wide_it pi = {1, 2, 3, 4, 5, 6, 7, 8};
  constexpr auto _0 = std::integral_constant<size_t,0>();
  constexpr auto _1 = std::integral_constant<size_t,1>();
  constexpr auto _2 = std::integral_constant<size_t,2>();
  constexpr auto _4 = std::integral_constant<size_t,4>();
  constexpr auto _8 = std::integral_constant<size_t,8>();

  std::cout << "---- simd" << '\n'
            << "<- pi                    = " << pi << '\n'
            << "-> swap_adjacent(pi, _0) = " << eve::swap_adjacent(pi, _0) << '\n'
            << "-> swap_adjacent(pi, _1) = " << eve::swap_adjacent(pi, _1) << '\n'
            << "-> swap_adjacent(pi, _2) = " << eve::swap_adjacent(pi, _2) << '\n'
            << "-> swap_adjacent(pi, _4) = " << eve::swap_adjacent(pi, _4) << '\n'
            << "-> swap_adjacent(pi, _8) = " << eve::swap_adjacent(pi, _8) << '\n'
;

//   std::uint64_t xf = 0xf0ff0fff0ffff00ULL;

//   std::cout << "---- scalar" << '\n'
//             << "<- xf          = " << std::hex << "0x" << xf << '\n'
//             << "-> swap_adjacent_groups(xf) = " << std::hex << "0x" << eve::swap_adjacent_groups(xf) << '\n';

}
