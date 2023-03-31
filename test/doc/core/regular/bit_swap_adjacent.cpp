
#include <eve/wide.hpp>
#include <iostream>
#include <bit>
#include <eve/module/core.hpp>

using wide_it = eve::wide<std::uint16_t, eve::fixed<8>>;

int main()
{
  wide_it pi = {1, 3, 7, 15, 31, 63, 127, 255};
  auto _0 = std::integral_constant<size_t, 0>();
  auto _2 = std::integral_constant<size_t, 2>();
  auto _4 = std::integral_constant<size_t, 4>();
  auto _8 = std::integral_constant<size_t, 8>();

  std::cout << "---- simd" << '\n'
            << "<- pi                        = " << pi << '\n'
            << "-> bit_swap_adjacent(pi, _0) = " << eve::bit_swap_adjacent(pi, _0) << '\n'
            << "-> bit_swap_adjacent(pi, _2) = " << eve::bit_swap_adjacent(pi, _2) << '\n'
            << "-> bit_swap_adjacent(pi, _4) = " << eve::bit_swap_adjacent(pi, _4) << '\n'
            << "-> bit_swap_adjacent(pi, _8) = " << eve::bit_swap_adjacent(pi, _8) << '\n';


  std::uint8_t xf = 48;

  std::cout << "---- scalar" << '\n'
            << "<- xf                        = " << +xf << '\n'
            << "-> bit_swap_adjacent(xf, _2) = " << +eve::bit_swap_adjacent(xf, _2) << '\n';
  return 0;
}
