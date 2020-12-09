#include <eve/function/derivative/cyl_bessel_y.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<4>>;

int main()
{
  wide_ft pf = { 0.0f, 1.0f, -1.0f, -0.5f};

  std::cout
    << "---- simd" << '\n'
    << "<- pf                   = " << pf << '\n'
    << "-> derivative(cyl_bessel_y)(pf) = " << eve::derivative(eve::cyl_bessel_y)(pf) << '\n';

  float xf = 1.0f;

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf                   = " << xf << '\n'
    << "-> derivative(cyl_bessel_y)(xf) = " << eve::derivative(eve::cyl_bessel_y)(xf) << '\n'
  return 0;
}
