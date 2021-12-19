//#include <eve/function/atanpi.hpp>
#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<4>>;

int main()
{
  wide_ft pf = { 0.0f, 1.0f, -1.0f, -0.5f};

  std::cout
    << "---- simd" << '\n'
    << "<- pf         = " << pf << '\n'
    << "-> atanpi(pf) = " << eve::atanpi(pf) << '\n';

  float xf = 1.0f;
  float yf = -2.0f;

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf         = " << xf << '\n'
    << "-> atanpi(xf) = " << eve::atanpi(xf) << '\n'
    << "<- yf         = " << yf << '\n'
    << "-> atanpi(yf) = " << eve::atanpi(yf) << '\n';
  return 0;
}
