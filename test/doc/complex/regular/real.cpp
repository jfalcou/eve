#include <eve/module/complex.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<4>>;
using z_t = eve::as_complex_t<wide_ft>;

int main()
{
  wide_ft ref = { 0.0f, 1.0f, -1.0f, eve::pi(eve::as(1.0f))};
  wide_ft imf = { eve::pi(eve::as(1.0f)), 0.0f, 1.0f, -1.0f};
  z_t z{ref, imf};

  std::cout
    << "---- simd" << '\n'
    << "<- z             = " << z << '\n'
    << "-> real(z)       = " << eve::real(z) << '\n';

  auto scz = eve::as_complex_t<float>(1, 2);

  std::cout
    << "---- scalar"  << '\n'
    << "<- scz       = " << scz << '\n'
    << "-> real(scz) = " << eve::real(scz) << '\n';
  return 0;
}
