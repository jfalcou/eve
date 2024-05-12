#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{
  wide_ft pf = {0.0f,1.0f, -1.0f, -2.0f,
                eve::mindenormal(eve::as<float>()), eve::inf(eve::as<float>()),
                eve::minf(eve::as<float>()), eve::nan(eve::as<float>())};

  std::cout << "---- simd" << '\n'
            << "<- pf                  = " << pf << '\n'
            << "-> is_not_finite(pf) = " << eve::is_not_finite(pf) << '\n';

  float xf = 1.0f;
  float yf = eve::mindenormal(eve::as<float>());

  std::cout << "---- scalar" << '\n'
            << "<- xf                = " << xf << '\n'
            << "-> is_not_finite(xf) = " << eve::is_not_finite(xf) << '\n'
            << "<- yf                = " << yf << '\n'
            << "-> is_not_finite(yf) = " << eve::is_not_finite(yf) << '\n';
  return 0;
}
