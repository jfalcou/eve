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
            << "<- pf            = " << pf << '\n'
            << "-> is_normal(pf) = " << eve::is_normal(pf) << '\n';

  float xf = 1.0f;
  float yf = eve::mindenormal(eve::as<float>());

  std::cout << "---- scalar" << '\n'
            << "<- xf            = " << xf << '\n'
            << "-> is_normal(xf) = " << eve::is_normal(xf) << '\n'
            << "<- yf            = " << yf << '\n'
            << "-> is_normal(yf) = " << eve::is_normal(yf) << '\n';
  return 0;
}
