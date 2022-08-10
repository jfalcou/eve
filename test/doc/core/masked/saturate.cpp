#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;
using wide_it = eve::wide<std::int64_t, eve::fixed<4>>;
using int_16 = eve::as<std::int16_t>;
using int_64 = eve::as<std::int64_t>;

int main()
{
  wide_ft pf = {-1.0f, 2.3f, 45000.7f, -64768.6f};
  wide_it pi = {-1, 2, -3, eve::valmax(eve::as<std::int64_t>())};

  std::cout << "---- simd" << '\n'
            << "<- pf                         = " << pf << '\n'
            << "-> saturate(pf, int_64()_)    = " << eve::saturate(pf, int_64()) << '\n'
            << "-> saturate(pf, int_16())     = " << eve::saturate(pf, int_16()) << '\n'
            << "<- pi                         = " << pi << '\n'
            << "-> saturate(pi, as(eve::as<double>())) = " << eve::saturate(pi, eve::as<double>()) << '\n';

  double        xf = -64768.4f;
  std::int64_t xi = -64768;

  std::cout << "---- scalar" << '\n'
            << "<- xf                         = " << xf << '\n'
            << "-> saturate(xf, int_64())     = " << eve::saturate(xf, int_64()) << '\n'
            << "<- xi                         = " << xi << '\n'
            << "-> saturate(xi, as(eve::as<double>())) = " << eve::saturate(xi, eve::as<double>()) << '\n';
  return 0;
}
