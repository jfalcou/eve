#include <eve/function/dist.hpp>
#include <eve/function/saturated/dist.hpp>
#include <eve/wide.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <iostream>

using wide_it = eve::wide<int16_t, eve::fixed<4>>;

int main()
{
  wide_it pf = {0, 1, -1, -eve::valmax(eve::as<int16_t>())};
  wide_it qf = {1, -1, 0, eve::valmax(eve::as<int16_t>())};

  std::cout << "---- simd" << '\n'
            << "<- pf                       = " << pf << '\n'
            << "<- qf                       = " << qf << '\n'
            << "-> dist(pf, qf)             = " << eve::dist(pf, qf) << '\n'
            << "-> saturated(dist)(pf, qf) = " << eve::saturated(eve::dist)(pf, qf)
            << '\n';

  int16_t xf = -eve::valmax(eve::as<int16_t>());
  int16_t yf = eve::valmax(eve::as<int16_t>());

  std::cout << "---- scalar" << '\n'
            << "<- xf                       = " << xf << '\n'
            << "<- yf                       = " << yf << '\n'
            << "-> dist(xf, yf)             = " << eve::dist(xf, yf) << '\n'
            << "-> saturated(dist)(xf, yf) = " << eve::saturated(eve::dist)(xf, yf)
            << '\n';
  return 0;
}
