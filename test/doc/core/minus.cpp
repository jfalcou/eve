#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;
using wide_it = eve::wide<std::int16_t, eve::fixed<4>>;

consteval auto constexpr_minus(auto a) { return eve::minus(a); }

int main()
{
  wide_ft pf = {-1.0f, 2.0f, -3.0f, -32768.0f};
  wide_it pi = {-1, 2, -3, -32768};

  std::cout << "---- simd" << '\n'
            << "<- pf                   = " << pf << '\n'
            << "-> minus(pf)            = " << eve::minus(pf) << '\n'

            << "<- pi                   = " << pi << '\n'
            << "-> minus(pi)            = " << eve::minus(pi) << '\n'
            << "-> minus[saturated](pi) = " << eve::minus[eve::saturated](pf) << '\n'
            << "-> minus[pf > -2](pf)   = " << eve::minus[pf > -2](pf) << '\n';

  float        xf = -32768.0f;
  std::int16_t xi = -32768;

  std::cout << "---- scalar" << '\n'
            << "<- xf        = " << xf << '\n'
            << "-> minus(xf) = " << eve::minus(xf) << '\n'
            << "<- xi        = " << xi << '\n'
            << "-> minus(xi) = " << eve::minus(xi) << '\n';

  std::cout << "-> constexpr_minus(1.0f) = " << constexpr_minus(1.0f) << std::endl;

  return 0;
}
