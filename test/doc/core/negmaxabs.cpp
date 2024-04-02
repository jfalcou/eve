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
            << "<- pf                           = " << pf << '\n'
            << "<- qf                           = " << qf << '\n'
            << "-> negmaxabs(pf, qf)            = " << eve::negmaxabs(pf, qf) << '\n'
            << "-> negmaxabs[pedantic}(pf, qf)  = " << eve::negmaxabs[eve::pedantic](pf, qf) << '\n'
            << "-> negmaxabs[numeric](pf, qf)   = " << eve::negmaxabs[eve::numeric](pf, qf) << '\n'
            << "-> negmaxabs[pf<-1.0f](pf, qf)  = " << eve::negmaxabs[pf < -1.0f](pf, qf) << '\n';

  float xf = -4.0f;
  float yf = 1.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf                           = " << xf << '\n'
            << "<- yf                           = " << yf << '\n'
            << "-> negmaxabs(xf, yf)            = " << eve::negmaxabs(xf, yf) << '\n'
            << "-> negmaxabs[pedantic}(xf, yf)  = " << eve::negmaxabs[eve::pedantic](xf, yf) << '\n'
            << "-> negmaxabs[numeric](xf, yf)   = " << eve::negmaxabs[eve::numeric](xf, yf) << '\n';

   return 0;
}
