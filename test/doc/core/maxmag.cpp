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
            << "-> maxmag(pf, qf)            = " << eve::maxmag(pf, qf) << '\n'
            << "-> pedantic(maxmag)(pf, qf) = " << eve::pedantic(eve::maxmag)(pf, qf) << '\n'
            << "-> numeric(maxmag)(pf, qf)  = " << eve::numeric(eve::maxmag)(pf, qf) << '\n'
            << "-> diff_1st(maxmag)(pf, qf)     = " << eve::diff_1st(eve::maxmag)(pf, qf) << '\n'
            << "-> diff_2nd(maxmag)(pf, qf)     = " << eve::diff_2nd(eve::maxmag)(pf, qf) << '\n';

  float xf = -4.0f;
  float yf = 1.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf                        = " << xf << '\n'
            << "<- yf                        = " << yf << '\n'
            << "-> maxmag(xf, yf)            = " << eve::maxmag(xf, yf) << '\n'
            << "-> pedantic(maxmag)(xf, yf) = " << eve::pedantic(eve::maxmag)(xf, yf) << '\n'
            << "-> numeric(maxmag)(xf, yf)  = " << eve::numeric(eve::maxmag)(xf, yf) << '\n';
   return 0;
}
