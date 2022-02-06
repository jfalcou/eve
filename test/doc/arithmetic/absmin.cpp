//#include <eve/function/absmin.hpp>
#include <eve/module/core.hpp>
#include <eve/function/pedantic/absmin.hpp>
#include <eve/function/numeric/absmin.hpp>
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
            << "-> absmin(pf, qf)            = " << eve::absmin(pf, qf) << '\n'
            << "-> pedantic(absmin)(pf, qf)  = " << eve::pedantic(eve::absmin)(pf, qf) << '\n'
            << "-> numeric(absmin)(pf, qf)   = " << eve::numeric(eve::absmin)(pf, qf) << '\n';

  float xf = -4.0f;
  float yf = 1.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf                        = " << xf << '\n'
            << "<- yf                        = " << yf << '\n'
            << "-> absmin(xf, yf)            = " << eve::absmin(xf, yf) << '\n'
            << "-> pedantic(absmin)(xf, yf)  = " << eve::pedantic(eve::absmin)(xf, yf) << '\n'
            << "-> numeric(absmin)(xf, yf)   = " << eve::numeric(eve::absmin)(xf, yf) << '\n';
   return 0;
}
