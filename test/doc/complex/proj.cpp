#include <eve/module/complex.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<4>>;
using z_t = eve::as_complex_t<wide_ft>;

int main()
{
  wide_ft ref = { 0.0f, 1.0f, eve::minf(eve::as(1.0f)), eve::inf(eve::as(1.0f))};
  wide_ft imf = { eve::inf(eve::as(1.0f)), 0.0f, 1.0f, eve::nan(eve::as(1.0f))};
  z_t z{ref, imf};

  std::cout
    << "---- simd" << '\n'
    << "<- z             = " << z << '\n'
    << "-> proj(z)       = " << eve::proj(z) << '\n';

  auto scz = eve::as_complex_t<float>(1,eve::inf(eve::as(1.0f)));

  std::cout
    << "---- scalar"  << '\n'
    << "<- scz       = " << scz << '\n'
    << "-> proj(scz) = " << eve::proj(scz) << '\n';
  return 0;
}
