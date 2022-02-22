#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <eve/module/math/constant/pi.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft pf = {1.0f, 0.0f, eve::inf(eve::as<float>()), 0.5f};

  std::cout << "---- simd" << '\n'
            << "<- pf              = " << pf << '\n'
            << "-> cscpi(pf)       = " << eve::cscpi(pf) << '\n'
            << "-> diff(cscpi)(pf) = " << eve::diff(eve::cscpi)(pf) << '\n';

  float xf = 3.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf        = " << xf << '\n'
            << "-> cscpi(xf) = " << eve::cscpi(xf) << '\n';
  return 0;
}
