//#include <eve/function/asec.hpp>
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
    << "<- pf       =  " << pf << '\n'
    << "-> asec(pf) = " << eve::asec(pf) << '\n';

  float xf = 1.0f;
  float yf = eve::inf(eve::as<float>());

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf       = " << xf << '\n'
    << "-> asec(xf) = " << eve::asec(xf) << '\n'
    << "<- yf =     = " << yf << '\n'
    << "-> asec(yf) = " << eve::asec(yf) << '\n';
  return 0;
}
