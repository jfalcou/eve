#include <eve/function/sqr.hpp>
#include <eve/function/saturated/sqr.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;
using wide_it = eve::wide<std::int16_t, eve::fixed<4>>;

int main()
{
  wide_ft pf = {-1.0f, 2.0f, -3.0f, 182.0f};
  wide_it pi = {-1, 2, -3, 182};

  std::cout << "---- simd" << '\n'
            << "<- pf                  = " << pf << '\n'
            << "-> sqr(pf)             = " << eve::sqr(pf) << '\n'
            << "<- pi                  = " << pi << '\n'
            << "-> saturated(sqr)(pi) = " << eve::saturated(eve::sqr)(pi) << '\n'
            << "-> sqr(pi)             = " << eve::sqr(pi) << '\n';

  float        xf = -32768.0f;
  std::int16_t xi = -32768;

  std::cout << "---- scalar" << '\n'
            << "<- xf                  = " << xf << '\n'
            << "-> sqr(xf)             = " << eve::sqr(xf) << '\n'
            << "<- xi                  = " << xi << '\n'
            << "-> saturated(sqr)(xi) = " << eve::saturated(eve::sqr)(xi) << '\n'
            << "-> sqr(xi)             = " << eve::sqr(xi) << '\n';
  return 0;
}
