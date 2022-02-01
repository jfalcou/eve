//#include <eve/function/acot.hpp>
#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <eve/module/core/constant/inf.hpp>
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<4>>;

int main()
{
  wide_ft pf = { 0.0f, 2.0f, -1.0f, -0.5f};

  std::cout
    << "---- simd" << '\n'
    << "<- pf            = " << pf << '\n'
    << "-> eve::acot(pf) = " << eve::acot(pf) << '\n';

  float xf = 1.0f;
  float yf = eve::inf(eve::as<float>());

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf            = " << xf << '\n'
    << "-> eve::acot(xf) = " << eve::acot(xf) << '\n'
    << "<- yf            = " << yf << '\n'
    << "-> eve::acot(yf) = " << eve::acot(yf) << '\n';
  return 0;
}
