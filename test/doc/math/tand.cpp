//#include <eve/function/tand.hpp>
#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/pi.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft pf = {1.0f, 0.0f, eve::inf(eve::as<float>()), 180.0f};

  std::cout << "---- simd" << '\n'
            << "<- pf       = " << pf << '\n'
            << "-> tand(pf) = " << eve::tand(pf) << '\n';

  float xf = 3.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf       = " << xf << '\n'
            << "-> tand(xf) = " << eve::tand(xf) << '\n';
  return 0;
}
