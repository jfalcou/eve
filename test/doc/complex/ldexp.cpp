#include <eve/module/complex.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<4>>;
using wide_it = eve::wide <std::int32_t, eve::fixed<4>>;

int main()
{
  wide_ft ref1 = { 0.0f, 1.0f, -1.0f, 0.5f};
  wide_ft imf1 = { 2.0f , -1.0,  -5.0, 0.0};
  auto z1 = eve::as_complex_t<wide_ft>(ref1, imf1);
  wide_it n = { 3 , -2,  -5, 0};

  std::cout
    << "---- simd" << std::endl
    << "<- z1          = " << z1 << std::endl
    << "<- n           = " << n << std::endl
    << "-> ldexp(z1,n) = " << eve::ldexp(z1,n) << std::endl;
  return 0;
}
