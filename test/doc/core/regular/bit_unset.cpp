
#include <eve/wide.hpp>
#include <iostream>
#include <bit>
#include <eve/module/core.hpp>

using wide_it = eve::wide<std::uint16_t, eve::fixed<8>>;

int main()
{
  wide_it pi = {1, 3, 7, 15, 31, 63, 127, 255};
  auto _1 = std::integral_constant<size_t, 1>();
  auto _2 = std::integral_constant<size_t, 2>();
  auto _3 = std::integral_constant<size_t, 3>();
  auto _4 = std::integral_constant<size_t, 4>();
  auto _8 = std::integral_constant<size_t, 8>();
  auto _17 = std::integral_constant<size_t, 17>();


  std::cout << "---- simd" << '\n'
            << "<- pi                = " << pi << '\n'
            << "-> bit_unset(pi, 0u) = " << eve::bit_unset(pi, 0u) << '\n'
            << "-> bit_unset(pi, _1) = " << eve::bit_unset(pi, _1) << '\n'
            << "-> bit_unset(pi, 1u) = " << eve::bit_unset(pi, 1u) << '\n'
            << "-> bit_unset(pi, _2) = " << eve::bit_unset(pi, _2) << '\n'
            << "-> bit_unset(pi, _3) = " << eve::bit_unset(pi, _3) << '\n'
            << "-> bit_unset(pi, _4) = " << eve::bit_unset(pi, _4) << '\n'
            << "-> bit_unset(pi, _8) = " << eve::bit_unset(pi, _8) << '\n'
            << "-> bit_unset(pi, _17)= " << eve::bit_unset(pi, _17) << '\n';


  std::uint8_t xf = 48;

  std::cout << "---- scalar" << '\n'
            << "<- xf              = " << +xf << '\n'
            << "-> bit_unset(xf, 5u) = " << +eve::bit_unset(xf, 5u) << '\n';
  return 0;
}
