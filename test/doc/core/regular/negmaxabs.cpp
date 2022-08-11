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
            << "-> negmaxabs(pf, qf)            = " << eve::negmaxabs(pf, qf) << '\n'
            << "-> pedantic(negmaxabs)(pf, qf) = " << eve::pedantic(eve::negmaxabs)(pf, qf) << '\n'
            << "-> numeric(negmaxabs)(pf, qf)  = " << eve::numeric(eve::negmaxabs)(pf, qf) << '\n';

  float xf = -4.0f;
  float yf = 1.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf                        = " << xf << '\n'
            << "<- yf                        = " << yf << '\n'
            << "-> negmaxabs(xf, yf)            = " << eve::negmaxabs(xf, yf) << '\n'
            << "-> pedantic(negmaxabs)(xf, yf) = " << eve::pedantic(eve::negmaxabs)(xf, yf) << '\n'
            << "-> numeric(negmaxabs)(xf, yf)  = " << eve::numeric(eve::negmaxabs)(xf, yf) << '\n';
   return 0;
}
