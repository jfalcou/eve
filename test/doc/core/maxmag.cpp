#include <eve/function/maxmag.hpp>
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
            << "-> maxmag(pf, qf)            = " << eve::maxmag(pf, qf) << '\n'
            << "-> pedantic_(maxmag)(pf, qf) = " << eve::pedantic_(eve::maxmag)(pf, qf) << '\n'
            << "-> numeric_(maxmag)(pf, qf)  = " << eve::numeric_(eve::maxmag)(pf, qf) << '\n';

  float xf = -4.0f;
  float yf = 1.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf                        = " << xf << '\n'
            << "<- yf                        = " << yf << '\n'
            << "-> maxmag(xf, yf)            = " << eve::maxmag(xf, yf) << '\n'
            << "-> pedantic_(maxmag)(xf, yf) = " << eve::pedantic_(eve::maxmag)(xf, yf) << '\n'
            << "-> numeric_(maxmag)(xf, yf)  = " << eve::numeric_(eve::maxmag)(xf, yf) << '\n';
   return 0;
}
