#include <eve/module/complex.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide <double, eve::fixed<4>>;

int main()
{
  wide_ft ref = { 1.0, 1.0, -1.0, 0.5};
  wide_ft imf = { 0.0 , -1.0,  -5.0, 0.0};
  auto z = eve::as_complex_t<wide_ft>(ref, imf);
  std::cout
    << "---- simd" << std::endl
    << "<- z             = " << z << std::endl
    << "-> faddeeva(z)  = " << eve::faddeeva(z) << std::endl;

}
