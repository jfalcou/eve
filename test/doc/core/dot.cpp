#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_it = eve::wide<int16_t, eve::fixed<4>>;

int main()
{
  wide_it pf = {0, 1, -1, -eve::valmax(eve::as<int16_t>())};
  wide_it qf = {1, -1, 0, eve::valmax(eve::as<int16_t>())};

  std::cout << "---- simd" << '\n'
            << "<- pf                       = " << pf << '\n'
            << "<- qf                       = " << qf << '\n'
            << "-> dot(pf, qf)             = " << eve::dot(pf, qf) << '\n';

  int16_t xf = -eve::valmax(eve::as<int16_t>());
  int16_t yf = eve::valmax(eve::as<int16_t>());

  std::cout << "---- scalar" << '\n'
            << "<- xf                       = " << xf << '\n'
            << "<- yf                       = " << yf << '\n'
            << "-> dot(xf, yf)             = " << eve::dot(xf, yf) << '\n';
  return 0;
}
