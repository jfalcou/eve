#include <eve/module/polynomial.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<double, eve::fixed<8>>;
using wide_it = eve::wide<int   , eve::fixed<8>>;

int main()
{

  wide_ft xd = {-0.1, -0.2, -0.3, -0.5, 0.0, 0.2, 0.3, 2.0};
  wide_it n = {0, 1, 2, 3, 4, 5, 6, 7};
  wide_it z(0);

  std::cout << "---- simd" << '\n'
            << "<- xd                      = " << xd << '\n'
            << "<- n                       = " << n  << '\n'
            << "-> condon_shortey(legendre)(n, z, xd) = " << eve::condon_shortey(eve::legendre)(n, z, xd) << '\n';

  double xs = 0.1;

  std::cout << "---- scalar" << '\n'
            << "<- xs               = " << xs << '\n'
            << "-> eve::condon_shortey(eve::legendre)(4, xs)   = " << eve::condon_shortey(eve::legendre)(4, 0, xs) << '\n';

  return 0;
}
