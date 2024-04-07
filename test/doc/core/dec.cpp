#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;
using wide_it = eve::wide<std::int8_t, eve::fixed<4>>;

int main()
{
  wide_ft pf = {0.0f, 1.0f, -1.0f, -2.0f};
  wide_it pi = {0, 1, -127, -128};

  std::cout << "---- simd" << '\n'
            << "<- pf                 = " << pf << '\n'
            << "-> dec(pf)            = " << eve::dec(pf) << '\n'
            << "-> dec[pf > 0.0f](pf) = " << eve::dec[pf > 0.0f](pf) << '\n'
            << "-> dec[saturated]pi)  = " << eve::dec[eve::saturated](pi) << '\n';

  float xf = 1.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf           = " << xf << '\n'
            << "-> eve::dec(xf) = " << eve::dec(xf) << '\n';

  return 0;
}
