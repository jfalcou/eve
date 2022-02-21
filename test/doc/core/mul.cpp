#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using w_t = eve::wide<std::int16_t, eve::fixed<4>>;
  w_t pi = {3, 2, 3, 32700}, qi = {4, 1, 1, 100};

  std::cout << "---- simd" << '\n'
            << " <- pi          = " << pi << '\n'
            << " <- qi          = " << qi << '\n'
            << " -> mul(pi, qi) = " << eve::mul(pi, qi) << '\n'
            << " -> pi * qi     = " << pi * qi << '\n';

  std::int16_t xi = 100, yi = 32700;

  std::cout << "---- scalar" << '\n'
            << " xi             = " << xi << '\n'
            << " yi             = " << yi << '\n'
            << " -> mul(xi, yi) = " << eve::mul(xi, yi) << '\n'
            << " -> xi * yi     = " << xi * yi << '\n'; // C++ promotion
  return 0;
}
