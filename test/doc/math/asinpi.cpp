//#include <eve/function/asinpi.hpp>
#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <eve/module/core/constant/inf.hpp>
#include <eve/module/core/constant/minf.hpp>
#include <eve/module/core/constant/nan.hpp>
#include <eve/module/core/constant/mindenormal.hpp>
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<8>>;

int main()
{
  wide_ft pf = { 0.0f, 1.0f, -1.0f, -2.0f
                , eve::mindenormal(eve::as<float>()), eve::inf(eve::as<float>()), eve::minf(eve::as<float>()), eve::nan(eve::as<float>()) };

  std::cout
    << "---- simd" << '\n'
    << "<- pf         = " << pf << '\n'
    << "-> asinpi(pf) = " << eve::asinpi(pf) << '\n';

  float xf = 1.0f;
  float yf = eve::nan(eve::as<float>());

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf         = " << xf << '\n'
    << "-> asinpi(xf) = " << eve::asinpi(xf) << '\n'
    << "<- yf         = " << yf << '\n'
    << "-> asinpi(yf) = " << eve::asinpi(yf) << '\n';
  return 0;
}
