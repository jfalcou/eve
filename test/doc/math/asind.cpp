//#include <eve/function/asind.hpp>
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
    << "-> asind(pf) = " << eve::asind(pf) << '\n'
    << "-> diff(asind)(pf)     = " << eve::diff(eve::asind)(pf) << '\n';

  float xf = 1.0f;
  float yf = eve::nan(eve::as<float>());

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf        = " << xf << '\n'
    << "-> asind(xf) = " << eve::asind(xf) << '\n'
    << "<- yf        = " << yf << '\n'
    << "-> asind(yf) = " << eve::asind(yf) << '\n';
  return 0;
}
