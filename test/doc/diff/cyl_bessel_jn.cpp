#include <eve/function/diff/cyl_bessel_jn.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<4>>;
using wide_it = eve::wide <int, eve::fixed<4>>;

int main()
{
  wide_ft pf = { 0.0f, 1.0f, -1.0f, -0.5f};
  wide_it n  = { 2, 2.5, 3, 3.5};

  std::cout
    << "---- simd" << '\n'
    << "<- n                          = " << pf << '\n'
    << "<- pf                         = " << n << '\n'
    << "-> diff(cyl_bessel_jn)(n, pf) = " << eve::diff(eve::cyl_bessel_jn)(n, pf) << '\n';

  float xf = 1.0f;

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf                         = " << xf << '\n'
    << "-> diff(cyl_bessel_jn)(3, xf) = " << eve::diff(eve::cyl_bessel_jn)(3, xf) << '\n';
  return 0;
}
