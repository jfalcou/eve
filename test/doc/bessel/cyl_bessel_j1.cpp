#include <eve/function/cyl_bessel_j1.hpp>
#include <eve/wide.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <iostream>

using wide_ft = eve::wide<double, eve::fixed<8>>;

int main()
{

  wide_ft x = {0.5, -1.5, 0.1, -1.0, 19.0, 25.0, 21.5, 10000.0};
  std::cout << "---- simd" << '\n'
            << "<- x                = " << x << '\n'
            << "-> cyl_bessel_j1(x) = " << eve::cyl_bessel_j1(x) << '\n';


  double xd = -1.0;

  std::cout << "---- scalar" << '\n'
            << "<- xd                = " << xd << '\n'
            << "-> cyl_bessel_j1(xd) = " << eve::cyl_bessel_j1(xd) << '\n';


  return 0;
}
