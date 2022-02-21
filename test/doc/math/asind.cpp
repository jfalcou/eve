#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<4>>;

int main()
{
  wide_ft pf = { 0.0f, 1.0f, -1.0f, -0.5f};

  std::cout
    << "---- simd" << '\n'
    << "<- pf        = " << pf << '\n'
    << "-> acosd(pf) = " << eve::acosd(pf) << '\n';

  float xf = 1.0f;
  float yf = eve::nan(eve::as<float>());

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf        = " << xf << '\n'
    << "-> acosd(xf) = " << eve::acosd(xf) << '\n'
    << "<- yf        = " << yf << '\n'
    << "-> acosd(yf) = " << eve::acosd(yf) << '\n';
  return 0;
}
