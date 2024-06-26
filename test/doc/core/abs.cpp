#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using eve::saturated;
using eve::wide;
using eve::as;
using std::int32_t;

using wide_ft = wide<float>;
using wide_it = wide<std::int32_t>;

consteval auto constexpr_abs(auto a) { return eve::abs(a); }

int main()
{
  wide_ft pf([](auto i, auto){ return i%2 ? i : -i;});
  wide_it pi = -eve::valmax(as<wide_it>()) - eve::iota(as<wide_it>{});
  wide_it ti([](auto i, auto){ return i < 2 ? 1 : 0;});

  std::cout << "---- simd" << '\n'
            << "<- pf                 = " << pf << '\n'
            << "-> abs(pf)            = " << eve::abs(pf) << '\n'
            << "<- pi                 = " << pi << '\n'
            << "-> abs(pi)            = " << eve::abs(pi) << '\n'
            << "-> abs[saturated](pi) = " << eve::abs[saturated](pi) << '\n'
            << "-> abs[ti > 0](pi)    = " << eve::abs[ti > 0](pi) << '\n';

  float        xf = -32768.0f;
  std::int16_t xi = -32768;

  std::cout << "---- scalar" << '\n'
            << "<- xf                 = " << xf << '\n'
            << "-> abs(xf)            = " << eve::abs(xf) << '\n'
            << "<- xi                 = " << xi << '\n'
            << "-> abs(xi)            = " << eve::abs(xi) << '\n';
  return 0;
}
