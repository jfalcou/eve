#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <cmath>

using wide_it = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_it pf = {0, 1, -1, -eve::valmax(eve::as<float>())};
  wide_it qf = {1, -1, 0, eve::valmax(eve::as<float>())};

  std::cout << "---- simd" << '\n'
            << "<- pf                          = " << pf << '\n'
            << "<- qf                          = " << qf << '\n'
            << "-> remainder(pf, qf)           = " << eve::remainder(pf, qf) << '\n'
            << "-> remainder[pf > qf](pf, qf)  = " << eve::remainder[pf > qf](pf, qf) << '\n';

  float xf = -eve::valmax(eve::as<float>());
  float yf = eve::valmax(eve::as<float>());

  std::cout << "---- scalar" << '\n'
            << "<- xf                = " << xf << '\n'
            << "<- yf                = " << yf << '\n'
            << "-> remainder(xf, yf) = " << eve::remainder(xf, yf) << '\n'
            << '\n';
  return 0;
}
