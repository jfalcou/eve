#include <eve/function/cyl_bessel_j.hpp>
#include <eve/wide.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <iostream>

using wide_ft = eve::wide<double, eve::fixed<8>>;

int main()
{

  wide_ft pd = {0.5, -1.5, 0.1, -1.0, 19.0, 25.0, 21.5, 10000.0};
  wide_ft n = {0, 1, 2, 3, 0, 1, 2, 3};

  std::cout << "---- simd" << '\n'
            << "<- pd                    = " << pd << '\n'
            << "<- n                     = " << n  << '\n'
            << "-> cyl_bessel_j(n, pd)   = " << eve::cyl_bessel_j(n, pd) << '\n'
            << "-> cyl_bessel_j(3, pd)   = " << eve::cyl_bessel_j(3, pd) << '\n'
            << "-> cyl_bessel_j(n, 0.1)  = " << eve::cyl_bessel_j(n, 0.1) << '\n';


  double xd = 3.0;

  std::cout << "---- scalar" << '\n'
            << "<- xd                    = " << xd << '\n'
            << "-> cyl_bessel_j(1.0, xd) = " << eve::cyl_bessel_j(1.0, xd) << '\n';


  return 0;
}
