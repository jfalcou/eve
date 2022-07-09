#include <eve/module/bessel.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<double, eve::fixed<8>>;

int main()
{

  wide_ft x = {0.5, 1.5, 0.1, 1.0, 19.0, 25.0, 21.5, 10000.0};
  wide_ft n = {0, 1, 15, 2, 25, 26, 3, 12};
  std::cout << "---- simd" << '\n'
            << "<- n                          = " << n << '\n'
            << "<- x                          = " << x << '\n'
            << "-> sph_bessel_yn(pf)          = " << eve::sph_bessel_yn(n, x) << '\n'
            ;


  double xd = 1.0;

  std::cout << "---- scalar" << '\n'
            << "<- xd                   = " << xd << '\n'
            << "-> sph_bessel_yn(3, xd) = " << eve::sph_bessel_yn(3, xd) << '\n';


  return 0;
}
