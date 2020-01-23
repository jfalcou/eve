#include <eve/function/bit.hpp>
#include <eve/constant/nan.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_it = eve::wide<std::uint32_t, eve::fixed<4>>;

int main()
{
  wide_it pi = {3, -2, 1, 0};
  wide_it qi = {4, -1, 5, 25};
  std::cout << "---- simd" << '\n'
            << " <- pi =                         " << pi << '\n'
            << " <- qi =                         " << qi << '\n'
            << " -> eve::bit_notand(pi, qi) = " << eve::bit_notand(pi, qi) << '\n';

  std::uint32_t xi = 3, yi = 5;

  std::cout << "---- scalar" << '\n'
            << " xi =                            " << xi << '\n'
            << " yi =                            " << yi << '\n'
            << " -> eve::bit_notand(xi, yi) = " << eve::bit_notand(xi, yi) << '\n';
  return 0;
}
