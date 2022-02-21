#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <eve/module/core/constant/inf.hpp>
#include <eve/module/core/constant/minf.hpp>
#include <eve/module/core/constant/nan.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{
 wide_ft pf = {0.0f, 1.0f, -1.0f, -2.0f, 2.0f,
               eve::inf(eve::as<float>()), eve::minf(eve::as<float>()), eve::nan(eve::as<float>())};

  std::cout << "---- simd" << '\n'
            << "<- pf             = " << pf << '\n'
            << "-> cbrt(pf)       = " << eve::cbrt(pf) << '\n'
            << "-> diff(cbrt)(pf) = " << eve::diff(eve::cbrt)(pf) << '\n';

  float xf = 1.0f;
  float yf = eve::nan(eve::as<float>());

  std::cout << "---- scalar" << '\n'
            << "<- xf       = " << xf << '\n'
            << "-> cbrt(xf) = " << eve::cbrt(xf) << '\n'
            << "<- yf       = " << yf << '\n'
            << "-> cbrt(yf) = " << eve::cbrt(yf) << '\n';
  return 0;
}
