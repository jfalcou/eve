#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;
using wide_it = eve::wide<std::int16_t, eve::fixed<4>>;

consteval auto constexpr_sqr(auto a) { return eve::sqr(a); }

int main()
{
  wide_ft pf = {-1.0f, 2.0f, -3.0f, 182.0f};
  wide_it pi = {-1, 2, -3, 182};

  std::cout << "---- simd" << '\n'
            << "<- pf                  = " << pf << '\n'
            << "-> sqr(pf)             = " << eve::sqr(pf) << '\n'
            << "-> sqr[pf < 0](pf)     = " << eve::sqr[pf < 0](pf) << '\n'
            << "<- pi                  = " << pi << '\n'
            << "-> sqr[saturated2](pi)  = " << eve::sqr[eve::saturated2](pi) << '\n'
            << "-> sqr(pi)             = " << eve::sqr(pi) << '\n';

  float        xf = -32768.0f;
  std::int16_t xi = -32768;

  std::cout << "---- scalar" << '\n'
            << "<- xf                  = " << xf << '\n'
            << "-> sqr(xf)             = " << eve::sqr(xf) << '\n'
            << "<- xi                  = " << xi << '\n'
            << "-> sqr[saturated2](xi)  = " << eve::sqr[eve::saturated2](xi) << '\n'
            << "-> sqr(xi)             = " << eve::sqr(xi) << '\n';

  std::cout << "-> constexpr_sqr(1.0f) = " << constexpr_sqr(1.0f) << std::endl;

  return 0;
}
