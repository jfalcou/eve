#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float, eve::fixed<4>>;
using wide_it = eve::wide<std::int16_t, eve::fixed<4>>;

int main()
{
  wide_ft pf = {-0.0f, 2.0f, eve::eps(eve::as<float>()), 0.0f};
  wide_it pi = {-1, 2, -3, -32};

  std::cout << "---- simd" << '\n'
            << "<- pf                  = " << std::setprecision(12) << pf << '\n'
            << "-> next(pf)            = " << eve::next(pf) << '\n'
            << "-> pedantic(next)(pf)  = " << eve::pedantic(eve::next)(pf) << '\n'
            << "<- pi                  = " << pi << '\n'
            << "-> next(pi)            = " << eve::next(pi) << '\n';

  float        xf = 0.0f;
  std::int16_t xi = -3;

  std::cout << "---- scalar" << '\n'
            << "<- xf                  = " << xf << '\n'
            << "-> next(xf, 3)         = " << eve::next(xf, 3) << '\n'
            << "<- xi                  = " << xi << '\n'
            << "-> next(xi)            = " << eve::next(xi) << '\n';
  return 0;
}
