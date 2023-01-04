#include <eve/module/complex.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<4>>;

int main()
{
  wide_ft ref1 = { 3.0f, 2.0f, 1.0f, 0.5f};
  wide_ft imf1 = { 2.0f , -1.0,  -5.0, 0.0};
  auto zc = eve::as_complex_t<wide_ft>(ref1, imf1);
  std::cout
    << "---- simd" << std::endl
    << "<- zc         = " << zc << std::endl
    << "-> lambda(zc) = " << eve::lambda(zc)<< std::endl;
   return 0;
}
