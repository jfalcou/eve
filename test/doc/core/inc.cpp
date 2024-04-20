#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<std::int8_t, eve::fixed<4>>;

int main()
{
  wide_ft pi = {127, 1, -127, -128};

  std::cout << "---- simd" << '\n'
            << "<- pi                             = " << pi << '\n'
            << "-> inc(pi)                        = " << eve::inc(pi) << '\n'
            << "-> inc[saturated](pi)             = " << eve::inc[eve::saturated](pi) << '\n'
            << "-> eve::inc[pi<0]                 = " << eve::inc[pi < 0](pi) << '\n'
            << "-> eve::inc[pi>0][saturated](pi)  = " << eve::inc[pi < 0][eve::saturated](pi) << '\n';

  return 0;

  float xf = 1.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf           = " << xf << '\n'
            << "-> eve::inc(xf) = " << eve::inc(xf) << '\n';

  return 0;
}
