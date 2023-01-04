#include <eve/module/complex.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<4>>;

int main()
{
  wide_ft ref1 = { 0.0f, 1.0f, -1.0f, 0.5f};
  wide_ft imf1 = { 2.0f , -1.0,  -5.0, 0.0};
  auto z1 = eve::as_complex_t<wide_ft>(ref1, imf1);
  wide_ft ref2 = { 4.0f, 0.0f, -1.0f, -0.5f};
  wide_ft imf2 = { -2.0f , 1.0,  3.0, 10.0};
  auto z2 = eve::as_complex_t<wide_ft>(ref2, imf2);

  std::cout
    << "---- simd" << std::endl
    << "<- z1                       = " << z1 << std::endl
    << "<- z2                       = " << z2 << std::endl
    << "-> rising_factorial(z1,z2)  = " << eve::rising_factorial(z1,z2) << std::endl;
  return 0;
}
