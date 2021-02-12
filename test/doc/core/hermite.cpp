#include <eve/function/hermite.hpp>
#include <eve/wide.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <iostream>

using wide_ft = eve::wide<double, eve::fixed<8>>;
using wide_it = eve::wide<int   , eve::fixed<8>>;

int main()
{

  wide_ft pd = {0.5, -1.5, 0.1, -1.0, 19.0, 25.0, 21.5, 10000.0};
  wide_it n = {0, 1, 2, 3, 0, 1, 2, 3};

  std::cout << "---- simd" << '\n'
            << "<- pd               = " << pd << '\n'
            << "<- n                = " << n  << '\n'
            << "-> hermite(n, pd)   = " << eve::hermite(n, pd) << '\n'
            << "-> hermite(3, pd)   = " << eve::hermite(3, pd) << '\n'
            << "-> hermite(n, 0.1)  = " << eve::hermite(n, 0.1) << '\n';


  double xd = 3.0;

  std::cout << "---- scalar" << '\n'
            << "<- xd               = " << xd << '\n'
            << "-> hermite(4, xd)   = " << eve::hermite(4, xd) << '\n';


  return 0;
}
