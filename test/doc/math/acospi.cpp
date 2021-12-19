//#include <eve/function/acospi.hpp>
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
    << "-> acospi(pf) = " << eve::acospi(pf) << '\n';

  float xf = 1.0f;
  float yf = eve::nan(eve::as<float>());

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf         = " << xf << '\n'
    << "-> acospi(xf) = " << eve::acospi(xf) << '\n'
    << "<- yf         = " << yf << '\n'
    << "-> acospi(yf) = " << eve::acospi(yf) << '\n';
  return 0;
}
