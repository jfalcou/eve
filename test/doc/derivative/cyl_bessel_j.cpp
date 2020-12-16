#include <eve/function/derivative/cyl_bessel_j.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<4>>;

int main()
{
  wide_ft pf = { 0.0f, 1.0f, -1.0f, -0.5f};

  std::cout
    << "---- simd" << '\n'
    << "<- pf                   = " << pf << '\n'
    << "-> derivative(cyl_bessel_j)(1, pf) = " << eve::derivative(eve::cyl_bessel_j)(1, pf) << '\n';

  float xf = 1.0f;

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf                   = " << xf << '\n'
    << "-> derivative(cyl_bessel_j)(1, xf) = " << eve::derivative(eve::cyl_bessel_j)(1, xf) << '\n';
  return 0;
}
