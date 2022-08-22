#include <eve/module/complex.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<4>>;

int main()
{
  wide_ft ref = { 0.0f, 1.0f, -1.0f, eve::inf(eve::as(1.0f))};
  wide_ft imf = { 2.0f , -1.0f,  -5.0f, eve::nan(eve::as(1.0f))};
  auto z = eve::as_complex_t<wide_ft>(ref, imf);

  std::cout
    << "---- simd" << std::endl
    << "<- z                = " << z << std::endl
    << "-> pedantic(abs)(z) = " << eve::pedantic(eve::abs)(z) << std::endl;
  return 0;
}
