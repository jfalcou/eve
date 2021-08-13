#include <eve/function/maxmag.hpp>
#include <eve/function/pedantic/absmax.hpp>
#include <eve/function/numeric/absmax.hpp>
#include <eve/wide.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
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
            << "-> absmax(pf, qf)            = " << eve::absmax(pf, qf) << '\n'
            << "-> pedantic(absmax)(pf, qf)  = " << eve::pedantic(eve::absmax)(pf, qf) << '\n'
            << "-> numeric(absmax)(pf, qf)   = " << eve::numeric(eve::absmax)(pf, qf) << '\n';

  float xf = -4.0f;
  float yf = 1.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf                        = " << xf << '\n'
            << "<- yf                        = " << yf << '\n'
            << "-> absmax(xf, yf)            = " << eve::absmax(xf, yf) << '\n'
            << "-> pedantic(absmax)(xf, yf)  = " << eve::pedantic(eve::absmax)(xf, yf) << '\n'
            << "-> numeric(absmax)(xf, yf)   = " << eve::numeric(eve::absmax)(xf, yf) << '\n';
   return 0;
}
