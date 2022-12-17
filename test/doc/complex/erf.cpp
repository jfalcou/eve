#include <eve/module/complex.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide <double, eve::fixed<8>>;

int main()
{
//   wide_ft ref = { 1.0f, 10.0f, -1.0f, 0.5f};
//   wide_ft imf = { 0.2f , 0.2,  -5.0, 0.0};
  wide_ft imf = {-0.1,   0.1,   1.,   1.,  -1.,   0.000001,   0., 0. };
  wide_ft ref = { 0.,   0.,   0.,   2.,   2.,   0.000002,   2., 0.0}; ref = -ref;
  auto z = eve::as_complex_t<wide_ft>(ref, imf);
  auto r = eve::erf(z);
  std::cout
    << "---- simd" << std::endl
    << "<- z       = " << z << std::endl
    << "-> erf(z)  = " << r << std::endl;

//   auto zs = eve::as_complex_t<float>(-1, -5);
//   auto rs = eve::erf(zs);
//   std::cout
//     << "---- scalar" << std::endl
//     << "<- zs        = " << zs << std::endl
//     << "-> erf(zs)   = " << rs << std::endl;
  return 0;
}
