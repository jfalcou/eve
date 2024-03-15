#include <eve/module/polynomial.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<double, eve::fixed<8>>;
using wide_it = eve::wide<int   , eve::fixed<8>>;

int main()
{

  wide_ft xd = {0.5, -1.5, 0.1, -1.0, 19.0, 25.0, 21.5, 10000.0};
  wide_it n = {0, 1, 2, 3, 4, 5, 6, 7};
  wide_it m = {0, 1, 2, 3, 4, 5, 6, 7};
  wide_ft x(0.5);
  using eve::associated;

  std::cout << "---- simd" << '\n'
            << "<- xd               = " << xd << '\n'
            << "<- n                = " << n  << '\n'
            << "<- m                = " << m  << '\n'
            << "<- x                = " << x  << '\n'
            << "-> laguerre[associated](n, m, xd)   = " << eve::laguerre[associated](n, m, xd) << '\n'
            << "-> laguerre[associated](3, m, xd)   = " << eve::laguerre[associated](3, m, xd) << '\n'
            << "-> laguerre[associated](n, 3, xd)   = " << eve::laguerre[associated](n, 3, xd) << '\n'
            << "-> laguerre[associated](n, m, 0.5)  = " << eve::laguerre[associated](n, m, 0.5) << '\n'
            << "-> laguerre[associated](n, m, x)    = " << eve::laguerre[associated](n, m, x)   << '\n';

  double xs = 0.1;

  std::cout << "---- scalar" << '\n'
            << "<- xs               = " << xs << '\n'
            << "-> laguerre[associated](2, 2, xs)   = " << eve::laguerre[associated](2, 2, xs) << '\n';

  return 0;
}
