#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_it = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_it pf = {0, 1, -1, -eve::valmax(eve::as<float>())/10};
  wide_it qf = {1, -1, 0, eve::valmax(eve::as<float>())/10};

  std::cout << "---- simd" << '\n'
            << "<- pf                       = " << pf << '\n'
            << "<- qf                       = " << qf << '\n'
            << "-> reldist(pf, qf)          = " << eve::reldist(pf, qf) << '\n';

  float xf = -eve::valmax(eve::as<float>())/10;
  float yf = eve::valmax(eve::as<float>())/10;

  std::cout << "---- scalar" << '\n'
            << "<- xf                       = " << xf << '\n'
            << "<- yf                       = " << yf << '\n'
            << "-> reldist(xf, yf)          = " << eve::reldist(xf, yf) << '\n';
  return 0;
}
