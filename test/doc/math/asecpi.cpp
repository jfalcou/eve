//#include <eve/function/asecpi.hpp>
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
    << "<- pf         = " << pf << '\n'
    << "-> asecpi(pf) = " << eve::asecpi(pf) << '\n';

  float xf = 1.0f;
  float yf = eve::inf(eve::as<float>());

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf         = " << xf << '\n'
    << "-> asecpi(xf) = " << eve::asecpi(xf) << '\n'
    << "<- yf         = " << yf << '\n'
    << "-> asecpi(yf) = " << eve::asecpi(yf) << '\n';
  return 0;
}
