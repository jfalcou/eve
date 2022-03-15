#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;
using wide_it = eve::wide<std::int16_t, eve::fixed<4>>;

int main()
{
  wide_ft x;
  wide_it y;

  std::cout << "---- simd" << '\n'
            << "-> sqrtvalmax(as<wide_ft>()  = " << eve::sqrtvalmax(eve::as<wide_ft>()) << '\n'
            << "-> sqrtvalmax(as<wide_it>()  = " << eve::sqrtvalmax(eve::as<wide_it>()) << '\n'
            << "-> sqrtvalmax(as(x))         = " << eve::sqrtvalmax(eve::as(x))        << '\n'
            << "-> sqrtvalmax(as(y))         = " << eve::sqrtvalmax(eve::as(y))        << '\n';

  float        xf;
  std::int16_t xi;

  std::cout << "---- scalar" << '\n'
            << "-> sqrtvalmax(as<float>()         = " << eve::sqrtvalmax(eve::as<float>()) << '\n'
            << "-> sqrtvalmax(as<std::int16_t>()  = " << eve::sqrtvalmax(eve::as<std::int16_t>()) << '\n'
            << "-> sqrtvalmax(as(xf))             = " << eve::sqrtvalmax(eve::as(xf)) << '\n'
            << "-> sqrtvalmax(as(xi))             = " << eve::sqrtvalmax(eve::as(xi)) << '\n';

  return 0;
}
