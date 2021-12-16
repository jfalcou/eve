//#include <eve/function/laguerre.hpp>
#include <eve/module/polynomial.hpp>
#include <eve/wide.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <iostream>

using wide_ft = eve::wide<double, eve::fixed<8>>;
using wide_it = eve::wide<int   , eve::fixed<8>>;

int main()
{

  wide_ft xd = {0.5, -1.5, 0.1, -1.0, 19.0, 25.0, 21.5, 10000.0};
  wide_it n = {0, 1, 2, 3, 4, 5, 6, 7};
  wide_ft x(0.5);

  std::cout << "---- simd" << '\n'
            << "<- xd               = " << xd << '\n'
            << "<- n                = " << n  << '\n'
            << "<- x                = " << x  << '\n'
            << "-> laguerre(n, xd)   = " << eve::laguerre(n, xd) << '\n'
            << "-> laguerre(3, xd)   = " << eve::laguerre(3, xd) << '\n'
            << "-> laguerre(n, 0.5)  = " << eve::laguerre(n, 0.5) << '\n'
            << "-> laguerre(n, x)    = " << eve::laguerre(n, x)   << '\n';

  double xs = 3.0;

  std::cout << "---- scalar" << '\n'
            << "<- xs               = " << xs << '\n'
            << "-> laguerre(4, xs)   = " << eve::laguerre(4, xs) << '\n';

  return 0;
}
