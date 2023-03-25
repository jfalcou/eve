
#include <eve/wide.hpp>
#include <iostream>
#include <bit>
#include <eve/module/core.hpp>

using wide_it = eve::wide<std::uint16_t, eve::fixed<8>>;

int main()
{
  wide_it pi = {1, 3, 7, 15, 31, 63, 127, 255};

  std::cout << "---- simd" << '\n'
            << "<- pi              = " << pi << '\n'
            << "-> bit_swap(pi, std::integral_constant<size_t, 1>{}) = " << eve::bit_swap(pi, std::integral_constant<size_t, 1>{} ) << '\n'
            << "-> bit_swap(pi, std::integral_constant<size_t, 2>{}) = " << eve::bit_swap(pi, std::integral_constant<size_t, 2>{} ) << '\n'
            << "-> bit_swap(pi, std::integral_constant<size_t, 4>{}) = " << eve::bit_swap(pi, std::integral_constant<size_t, 4>{} ) << '\n'
            << "-> bit_swap(pi, std::integral_constant<size_t, 8>{}) = " << eve::bit_swap(pi, std::integral_constant<size_t, 8>{} ) << '\n';


  std::uint8_t xf = 48;

  std::cout << "---- scalar" << '\n'
            << "<- xf              = " << +xf << '\n'
            << "-> bit_swap(xf, std::integral_constant<size_t, 2>{}) = " << +eve::bit_swap(xf, std::integral_constant<size_t, 2>{}) << '\n';
  return 0;
}
