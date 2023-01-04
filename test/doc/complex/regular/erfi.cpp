#include <eve/module/complex.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide <double, eve::fixed<8>>;

int main()
{
  wide_ft ref = {-0.1,   0.1,   1.,   1.,  -1.,   0.000001,   0., 0. };
  wide_ft imf = { 0.,   0.,   0.,   2.,   2.,   0.000002,   2., 0.0};
  auto z = eve::as_complex_t<wide_ft>(ref, imf);
  auto r = eve::erfi(z);
  auto rr= -eve::i(eve::as(z))*eve::erf(eve::i(eve::as(z))*z);
  std::cout
    << "---- simd" << std::endl
    << "<- z       = " << z << std::endl
    << "-> erfi(z)  = " << r << std::endl
    << "-> erfi(z)  = " << rr<< std::endl  ;

  auto zs = eve::as_complex_t<float>(-1, -5);
  auto rs = eve::erfi(zs);
  std::cout
    << "---- scalar" << std::endl
    << "<- zs         = " << zs << std::endl
    << "-> erfi(zs)   = " << rs << std::endl;
  return 0;
}
