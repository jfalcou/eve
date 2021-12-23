//#include <eve/function/asin.hpp>
#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<4>>;

int main()
{
  wide_ft pf = { 0.0f, 1.0f, -1.0f, -0.5f};

  std::cout
    << "---- simd" << '\n'
    << "<- pf       = " << pf << '\n'
    << "-> asin(pf) = " << eve::asin(pf) << '\n';

  float xf = 1.0f;
  float yf = eve::nan(eve::as<float>());

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf       = " << xf << '\n'
    << "-> asin(xf) = " << eve::asin(xf) << '\n'
    << "<- yf       = " << yf << '\n'
    << "-> asin(yf) = " << eve::asin(yf) << '\n';
  return 0;
}
