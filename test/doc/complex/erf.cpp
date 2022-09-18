#include <eve/module/complex.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide <double, eve::fixed<4>>;

int main()
{
  wide_ft ref = { 1.0f, 10.0f, -1.0f, 0.5f};
  wide_ft imf = { 0.2f , 0.2,  -5.0, 0.0};
  auto z = eve::as_complex_t<wide_ft>(ref, imf);
  auto r = eve::erf(z);
  std::cout
    << "---- simd" << std::endl
    << "<- z       = " << z << std::endl
    << "-> erf(z)  = " << r << std::endl;

  auto zs = eve::as_complex_t<float>(-1, -5);
  std::cout
    << "---- scalar" << std::endl
    << "<- zs       = " << zs << std::endl
    << "-> erf(z)   = " << r << std::endl;
  return 0;
}
