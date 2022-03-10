#include <eve/module/polynomial.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<double, eve::fixed<8>>;
using wide_it = eve::wide<int   , eve::fixed<8>>;

int main()
{

  wide_ft xd = {0.5, -1.5, 0.1, -1.0, 19.0, 25.0, 21.5, 10000.0};
  wide_it n = {0, 1, 2, 3, 4, 5, 6, 7};
  wide_ft x(2.0);

  std::cout << "---- simd" << '\n'
            << "<- xd                  = " << xd << '\n'
            << "<- n                   = " << n  << '\n'
            << "<- x                   = " << x  << '\n'
            << "-> tchebytchev(n, xd)      = " << eve::tchebytchev(n, xd) << '\n'
            << "-> tchebytchev(3, xd)      = " << eve::tchebytchev(3, xd) << '\n'
            << "-> tchebytchev(n, 2.0)     = " << eve::tchebytchev(n, 2.0) << '\n'
            << "-> tchebytchev(n, x)       = " << eve::tchebytchev(n, x)   << '\n'
            << "-> diff(tchebytchev)(n, x) = " << eve::diff(eve::tchebytchev)(n, x) << '\n';

  double xs = 3.0;

  std::cout << "---- scalar" << '\n'
            << "<- xs               = " << xs << '\n'
            << "-> tchebytchev(4, xs)   = " << eve::tchebytchev(4, xs) << '\n';

  return 0;
}
