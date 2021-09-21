#include <eve/function/gegenbauer.hpp>
#include <eve/wide.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <iostream>

using wide_ft = eve::wide<double, eve::fixed<8>>;
using wide_it = eve::wide<unsigned, eve::fixed<8>>;

int main()
{

  wide_ft xd = {0.5, -1.5, 0.1, -1.0, 19.0, 25.0, 21.5, 10000.0};
  wide_it n = {0, 1, 2, 3, 4, 5, 6, 7};
  wide_ft x(0.3);
  wide_ft l(-3.0/8.0);
  std::cout << "---- simd" << '\n'
            << "<- xd                     = " << xd << '\n'
            << "<- n                      = " << n  << '\n'
            << "<- l                      = " << l  << '\n'
            << "<- x                      = " << x  << '\n'
            << "-> gegenbauer(n, l, xd)   = " << eve::gegenbauer(n, l, xd) << '\n'
            << "-> gegenbauer(3, l, xd)   = " << eve::gegenbauer(3, l, xd) << '\n'
            << "-> gegenbauer(n, l, 0.3)  = " << eve::gegenbauer(n, l, 0.3) << '\n'
            << "-> gegenbauer(n, -3.0/8.0, 0.3)  = " << eve::gegenbauer(n, -3.0/8.0, 0.3) << '\n'
            << "-> gegenbauer(n, l, x)    = " << eve::gegenbauer(n, l, x)   << '\n';

  double xs = 3.0;
  double ll = 0.1;
  std::cout << "---- scalar" << '\n'
            << "<- xs                     = " << xs << '\n'
            << "<- ll                     = " << ll  << '\n'
            << "-> gegenbauer(4, ll, xs)  = " << eve::gegenbauer(4, ll, xs) << '\n';

  return 0;
}
