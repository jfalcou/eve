#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;
using wide_it = eve::wide<std::int16_t, eve::fixed<4>>;
using wide_uit = eve::wide<std::uint16_t, eve::fixed<4>>;

int main()
{
  wide_ft pf = {-0.0f, 2.0f, -3.0f, -32768.0f,
                 0.0f, -2.0f, 3.0f, 32768.0f};
  wide_it pi = { 0, 2, -3, -32768};
  wide_uit pui = { 0, 2, 3, 32768};

  std::cout << "---- simd" << '\n'
            << "<- pf                    = " << pf << '\n'
            << "-> sign(pf)              = " << eve::sign(pf) << '\n'
            << "-> sign[abs(pf) < 2](pf) = " << eve::sign[eve::abs(pf) < 2](pf) << '\n'
            << "<- pi                    = " << pi << '\n'
            << "<- pui                   = " << pui << '\n'
            << "-> sign(pi)              = " << eve::sign(pi) << '\n'
            << "-> sign(pui)             = " << eve::sign(pui) << '\n';

  float        xf = -327.68f;
  std::int16_t xi = -328;
  std::uint8_t xui = 0;

  std::cout << "---- scalar" << '\n'
            << "<- xf       = " << xf << '\n'
            << "-> sign(xf) = " << eve::sign(xf) << '\n'
            << "<- xi       = " << xi << '\n'
            << "-> sign(xi) = " << eve::sign(xi) << '\n'
            << "<- xui       = " << +xui << '\n'
            << "-> sign(xui) = " << +eve::sign(xui) << '\n';
  return 0;
}
