#include <eve/function/gegenbauer.hpp>
#include <eve/wide.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <iostream>
#include <boost/math/special_functions/gegenbauer.hpp>

using wide_ft = eve::wide<double, eve::fixed<8>>;
using wide_it = eve::wide<int   , eve::fixed<8>>;

int main()
{

  wide_ft xd = {0.5, -1.5, 0.1, -1.0, 19.0, 25.0, 21.5, 10000.0};
  wide_it n = {0, 1, 2, 3, 4, 5, 6, 7};
  wide_ft x(2.0);

  std::cout << "---- simd" << '\n'
            << "<- xd               = " << xd << '\n'
            << "<- n                = " << n  << '\n'
            << "<- x                = " << x  << '\n'
            << "-> gegenbauer(n, xd)   = " << eve::gegenbauer(n, xd) << '\n'
            << "-> gegenbauer(3, xd)   = " << eve::gegenbauer(3, xd) << '\n'
            << "-> gegenbauer(n, 2.0)  = " << eve::gegenbauer(n, 2.0) << '\n'
            << "-> gegenbauer(n, x)    = " << eve::gegenbauer(n, x)   << '\n';

  double xs = 3.0;

  std::cout << "---- scalar" << '\n'
            << "<- xs               = " << xs << '\n'
            << "-> gegenbauer(4, xs)   = " << eve::gegenbauer(4, xs) << '\n';

  return 0;
}
