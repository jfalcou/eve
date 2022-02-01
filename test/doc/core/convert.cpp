#include <eve/function/convert.hpp>
#include <eve/function/saturated/convert.hpp>
#include <eve/function/converter.hpp>
#include <eve/module/core/constant/valmax.hpp>
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
            << "<- pf                                 = " << pf << '\n'
            << "-> convert(pf, int_64()_)             = " << eve::convert(pf, int_64()) << '\n'
            << "-> saturated(convert)(pf, int_16())   = " << eve::saturated(eve::convert)(pf, int_16()) << '\n'
            << "-> convert(pf, int_16()) =            = " << eve::convert(pf, int_16()) << '\n'
            << "<- pi                                 = " << pi << '\n'
            << "-> convert(pi, as(eve::as<double>())) = " << eve::convert(pi, eve::as<double>()) << '\n';

  double        xf = -64768.4f;
  std::int64_t xi = -64768;

  std::cout << "---- scalar" << '\n'
            << "<- xf                                  = " << xf << '\n'
            << "-> convert(xf, int_64())               = " << eve::convert(xf, int_64()) << '\n'
            << "<- xi                                  = " << xi << '\n'
            << "-> convert(xi, eve::as<double>())      = " << eve::convert(xi, eve::as<double>()) << '\n';
  return 0;
}
