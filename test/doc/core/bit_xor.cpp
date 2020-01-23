#include <eve/function/bit.hpp>
#include <eve/constant/nan.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_it = eve::wide<std::uint32_t, eve::fixed<4>>;

int main()
{
  wide_it pi = {3, 2, 10, 1};
  wide_it qi = {4, 1, 2, 5};
  std::cout << "---- simd" << '\n'
            << " <- pi =                      " << pi << '\n'
            << " <- qi =                      " << qi << '\n'
            << " -> eve::bit_xor(pi, qi) = " << eve::bit_xor(pi, qi) << '\n';

  std::uint32_t xi = 3, yi = 7;

  std::cout << "---- scalar" << '\n'
            << " xi =                         " << xi << '\n'
            << " yi =                         " << yi << '\n'
            << " -> eve::bit_xor(xi, yi) = " << eve::bit_xor(xi, yi) << '\n';
  return 0;
}
