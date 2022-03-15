#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;
using wide_it = eve::wide<std::int16_t, eve::fixed<4>>;

int main()
{
  wide_ft x;
  wide_it y;

  std::cout << "---- simd" << '\n'
            << "-> valmax(as<wide_ft>()  = " << eve::valmax(eve::as<wide_ft>()) << '\n'
            << "-> valmax(as<wide_it>()  = " << eve::valmax(eve::as<wide_it>()) << '\n'
            << "-> valmax(as(x))         = " << eve::valmax(eve::as(x))        << '\n'
            << "-> valmax(as(y))         = " << eve::valmax(eve::as(y))        << '\n';

  float        xf;
  std::int16_t xi;

  std::cout << "---- scalar" << '\n'
            << "-> valmax(as<float>()         = " << eve::valmax(eve::as<float>()) << '\n'
            << "-> valmax(as<std::int16_t>()  = " << eve::valmax(eve::as<std::int16_t>()) << '\n'
            << "-> valmax(as(xf))             = " << eve::valmax(eve::as(xf)) << '\n'
            << "-> valmax(as(xi))             = " << eve::valmax(eve::as(xi)) << '\n';

  return 0;
}
