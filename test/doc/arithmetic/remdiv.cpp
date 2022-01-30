//#include <eve/function/rem.hpp>
#include <eve/module/arithmetic.hpp>
#include <iostream>

int main()
{
  using w_t = eve::wide<std::int16_t, eve::fixed<4>>;
  w_t pi = {3, 2, 3, 32700}, qi = {4, 2, 2, 101};

  std::cout << "---- simd" << '\n'
            << " <- pi =          " << pi << '\n'
            << " <- qi =          " << qi << '\n'
            << " -> rem(pi, qi) = " << eve::rem(pi, qi) << '\n'
            << " -> pi % qi     = " << pi % qi << '\n';

  std::int16_t xi  = 32700,  yi = 101;

  std::cout << "---- scalar" << '\n'
            << " xi =             " << xi << '\n'
            << " yi =             " << yi << '\n'
            << " -> rem(xi, yi) = " << eve::rem(xi, yi) << '\n'
            << " -> xi % yi     = " << xi % yi << '\n';
  return 0;
}
