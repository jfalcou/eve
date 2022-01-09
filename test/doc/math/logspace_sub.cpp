//#include <eve/function/logspace_sub.hpp>
#include <eve/module/math.hpp>

#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using w_t = eve::wide<float, eve::fixed<4>>;
  w_t pi = {3, 2, 3, 3}, qi = {4, 1, 1, ~0};

  std::cout << "---- simd" << '\n'
            << " <- pi                   = " << pi << '\n'
            << " <- qi                   = " << qi << '\n'
            << " -> logspace_sub(pi, qi) = " << eve::logspace_sub(pi, qi) << '\n';

  float xi = 3, yi = 4;

  std::cout << "---- scalar" << '\n'
            << " xi                      = " << xi << '\n'
            << " yi                      = " << yi << '\n'
            << " -> logspace_sub(xi, yi) = " << eve::logspace_sub(xi, yi) << '\n';
  return 0;
}
