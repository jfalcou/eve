#include <eve/function/diff/cyl_bessel_y.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<4>>;

int main()
{
  wide_ft pf = { 0.0f, 1.0f, -1.0f, -0.5f};

  std::cout
    << "---- simd" << '\n'
    << "<- pf                   = " << pf << '\n'
    << "-> diff(cyl_bessel_y)(1, pf) = " << eve::diff(eve::cyl_bessel_y)(1, pf) << '\n';

  float xf = 1.0f;

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf                   = " << xf << '\n'
    << "-> diff(cyl_bessel_y)(1, xf) = " << eve::diff(eve::cyl_bessel_y)(1, xf) << '\n';
  return 0;
}
