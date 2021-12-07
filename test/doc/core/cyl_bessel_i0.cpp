#include <eve/function/cyl_bessel_i0.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<double, eve::fixed<8>>;

int main()
{

  wide_ft pd = {0.5, -1.5, 0.1, -1.0, 19.0, 25.0, 21.5, 10000.0};
  std::cout << "---- simd" << '\n'
            << "<- pd                = " << pd << '\n'
            << "-> cyl_bessel_i0(pd) = " << eve::cyl_bessel_i0(pd) << '\n';


  double xd = -1.0;

  std::cout << "---- scalar" << '\n'
            << "<- xd                = " << xd << '\n'
            << "-> cyl_bessel_i0(xd) = " << eve::cyl_bessel_i0(xd) << '\n';


  return 0;
}
