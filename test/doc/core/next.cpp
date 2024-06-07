#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float, eve::fixed<8>>;
using wide_it = eve::wide<std::int16_t, eve::fixed<4>>;

consteval auto constexpr_next(auto a) { return eve::next(a); }

int main()
{
  wide_ft pf = {-0.0f, 2.0f, eve::eps(eve::as<float>()), 0.0f, 30.0f,eve::mindenormal(eve::as<float>()),
                eve::inf(eve::as<float>()), eve::nan(eve::as<float>())};
  wide_it pi = {-1, 2, -3, 32767};

  std::cout << "---- simd" << std::setprecision(12) << '\n'
            << "<- pf                    = "  << pf << '\n'
            << "-> next(pf)              = " << eve::next(pf) << '\n'
            << "-> next[pedantic2](pf)   = " << eve::next[eve::pedantic2](pf) << '\n'
            << "-> next[pf > 0](pf)      = " << eve::next[pf > 0](pf) << '\n'
            << "-> next[saturated2](pf)  = " << eve::next[eve::saturated2](pf) << '\n'
            << "<- pi                    = " << pi << '\n'
            << "-> next(pi)              = " << eve::next(pi) << '\n'
            << "-> next[saturated2](pi)   = " << eve::next[eve::saturated2](pi) << '\n';

  float        xf = 0.0f;
  std::int16_t xi = -3;

  std::cout << "---- scalar" << '\n'
            << "<- xf                  = " << xf << '\n'
            << "-> next(xf, 3)         = " << eve::next(xf, 3) << '\n'
            << "<- xi                  = " << xi << '\n'
            << "-> next(xi)            = " << eve::next(xi) << '\n';

  std::cout << "-> constexpr_next(1) = " << constexpr_next(1) << std::endl;

  return 0;
}
