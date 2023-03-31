
#include <eve/wide.hpp>
#include <iostream>
#include <eve/module/core.hpp>

using wide_it = eve::wide<std::uint32_t, eve::fixed<4>>;

int main()
{
  wide_it pi = {0x0fU, 0xf0f0U, 0x0f0f0fU, 0xf0f0f0f0f0U};
  auto _0 = std::integral_constant<size_t, 0>();
  auto _1 = std::integral_constant<size_t, 1>();
  auto _2 = std::integral_constant<size_t, 2>();
  auto _4 = std::integral_constant<size_t, 4>();
  using eve::is_odd;
  std::cout << "---- simd" << '\n'
            << "<- pi                                     = " << pi << '\n'
            << "-> byte_swap_adjacent[is_odd(pi)](pi, _0) = " << eve::byte_swap_adjacent[is_odd(pi)](pi, _0) << '\n'
            << "-> byte_swap_adjacent[is_odd(pi)](pi, _1) = " << eve::byte_swap_adjacent[is_odd(pi)](pi, _1) << '\n'
            << "-> byte_swap_adjacent[is_odd(pi)](pi, _2) = " << eve::byte_swap_adjacent[is_odd(pi)](pi, _2) << '\n'
            << "-> byte_swap_adjacent[is_odd(pi)](pi, _4) = " << eve::byte_swap_adjacent[is_odd(pi)](pi, _4) << '\n';


  std::uint64_t xf = 0xff00ff00ff00ff00ULL;

  std::cout << "---- scalar" << '\n'
            << "<- xf                                      = " << std::hex << "0x" << xf << '\n'
            << "-> byte_swap_adjacent[is_odd(pi)](xf, _1)  = " << std::hex << "0x0" << eve::byte_swap_adjacent[eve::is_odd(pi)](xf,_1) << '\n'
            << "-> byte_swap_adjacent[is_even(pi)](xf, _1) = " << std::hex << "0x00"<< eve::byte_swap_adjacent[eve::is_odd(pi)](xf,_1) << '\n';
  return 0;
}
