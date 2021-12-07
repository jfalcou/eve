#include <eve/function/cyl_bessel_kn.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<double, eve::fixed<8>>;

int main()
{

  wide_ft x = {0.5, 1.5, 0.1, 1.0, 19.0, 25.0, 21.5, 10000.0};
  wide_ft n = {0.5, -1.0, 1.5, -2.0, 2.5, -2.6, 3.2, -12};
  std::cout << "---- simd" << '\n'
            << "<- n                 = " << n << '\n'
            << "<- x                 = " << x << '\n'
            << "-> cyl_bessel_kn(pd) = " << eve::cyl_bessel_kn(n, x) << '\n';


  double xd = 1.0;

  std::cout << "---- scalar" << '\n'
            << "<- xd                   = " << xd << '\n'
            << "-> cyl_bessel_kn(3, xd) = " << eve::cyl_bessel_kn(3, xd) << '\n';


  return 0;
}
