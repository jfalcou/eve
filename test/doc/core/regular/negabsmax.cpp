#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{
  wide_ft pf = {0.0f, 1.0f,  1.0f, -2.0f, 2.0f,
                eve::inf(eve::as<float>()), eve::minf(eve::as<float>()), eve::nan(eve::as<float>())};
  wide_ft qf = {4.0f, 1.0f, -1.0f,  0.0f,  -3.0f,
                eve::nan(eve::as<float>()),  -eve::nan(eve::as<float>()), -2.0f};

  std::cout << "---- simd" << '\n'
            << "<- pf                        = " << pf << '\n'
            << "<- qf                        = " << qf << '\n'
            << "-> negabsmax(pf, qf)            = " << eve::negabsmax(pf, qf) << '\n'
            << "-> negabsmax[pedantic](pf, qf) = " << eve::negabsmax[eve::pedantic](pf, qf) << '\n'
            << "-> negabsmax[numeric](pf, qf)  = " << eve::negabsmax[eve::numeric](pf, qf) << '\n';

  float xf = -4.0f;
  float yf = 1.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf                        = " << xf << '\n'
            << "<- yf                        = " << yf << '\n'
            << "-> negabsmax(xf, yf)            = " << eve::negabsmax(xf, yf) << '\n'
            << "-> negabsmax[pedantic](xf, yf) = " << eve::negabsmax[eve::pedantic](xf, yf) << '\n'
            << "-> negabsmax[numeric](xf, yf)  = " << eve::negabsmax[eve::numeric](xf, yf) << '\n';

   return 0;
}
