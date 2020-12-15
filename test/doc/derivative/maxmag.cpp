#include <eve/function/derivative/maxmag.hpp>
#include <eve/wide.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{
  wide_ft pf = {2.0f, 3.0f, -4.0f, 2.0f, 2.0f,
                eve::inf(eve::as<float>()), eve::minf(eve::as<float>()), eve::nan(eve::as<float>())};
  wide_ft qf = {4.0f, 1.0f, -1.0f,  0.5f,  0.0f,
                -2.0f, -3.0f,  2.5f};

  std::cout << "---- simd" << '\n'
            << "<- pf                              = " << pf << '\n'
            << "<- qf                              = " << qf << '\n'
            << "-> maxmag(pf, qf)                     = " << eve::maxmag(pf, qf) << '\n'
            << "-> derivative_1st(maxmag)(pf, qf)     = " << eve::derivative_1st(eve::maxmag)(pf, qf) << std::endl
            << "-> derivative_2nd(maxmag)(pf, qf)     = " << eve::derivative_2nd(eve::maxmag)(pf, qf) << std::endl;

  float xf = 4.0f;
  float yf = -1.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf                          = " << xf << '\n'
            << "<- yf                          = " << yf << '\n'
            << "-> maxmag(xf, yf)                 = " << eve::maxmag(xf, yf) << '\n'
            << "-> derivative_1st(maxmag)(xf, yf) = " << eve::derivative_1st(eve::maxmag)(xf, yf) << std::endl
            << "-> derivative_2nd(maxmag)(xf, yf) = " << eve::derivative_2nd(eve::maxmag)(xf, yf) << std::endl;
  return 0;
}
