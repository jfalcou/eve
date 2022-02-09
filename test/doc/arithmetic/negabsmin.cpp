//#include <eve/function/negabsmin.hpp>
#include <eve/module/core.hpp>
#include <eve/function/pedantic/negabsmin.hpp>
#include <eve/function/numeric/negabsmin.hpp>
#include <eve/wide.hpp>
#include <eve/module/core/constant/inf.hpp>
#include <eve/module/core/constant/minf.hpp>
#include <eve/module/core/constant/nan.hpp>
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
            << "-> negabsmin(pf, qf)            = " << eve::negabsmin(pf, qf) << '\n'
            << "-> pedantic(negabsmin)(pf, qf) = " << eve::pedantic(eve::negabsmin)(pf, qf) << '\n'
            << "-> numeric(negabsmin)(pf, qf)  = " << eve::numeric(eve::negabsmin)(pf, qf) << '\n';

  float xf = -4.0f;
  float yf = 1.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf                        = " << xf << '\n'
            << "<- yf                        = " << yf << '\n'
            << "-> negabsmin(xf, yf)            = " << eve::negabsmin(xf, yf) << '\n'
            << "-> pedantic(negabsmin)(xf, yf) = " << eve::pedantic(eve::negabsmin)(xf, yf) << '\n'
            << "-> numeric(negabsmin)(xf, yf)  = " << eve::numeric(eve::negabsmin)(xf, yf) << '\n';
   return 0;
}
