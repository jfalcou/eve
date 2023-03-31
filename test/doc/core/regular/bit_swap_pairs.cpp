
#include <eve/wide.hpp>
#include <iostream>
#include <bit>
#include <eve/module/core.hpp>

using wide_it = eve::wide<std::uint16_t, eve::fixed<8>>;

int main()
{
  wide_it pi = {1, 3, 7, 15, 31, 63, 127, 255};
  auto _0 = std::integral_constant<size_t, 0>();
  auto _15 = std::integral_constant<size_t, 15>();
  auto _16 = std::integral_constant<size_t, 16>();

  std::cout << "---- simd" << '\n'
            << "<- pi                                   = " << pi << '\n'
            << "-> bit_swap_pairs(pi, 0u, 15u)) = " << eve::bit_swap_pairs(pi, 0u, 15u) << '\n'
            << "-> bit_swap_pairs(pi, _0, _15)) = " << eve::bit_swap_pairs(pi, _0, _15) << '\n'
            << "-> bit_swap_pairs(pi, _0, _16)) = " << eve::bit_swap_pairs(pi, _0, _16) << '\n';

  return 0;
}
