#include <eve/module/core/constant/valmin.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;
using wide_it = eve::wide<std::int16_t, eve::fixed<4>>;

int main()
{
  wide_ft x;
  wide_it y;

  std::cout << "---- simd" << '\n'
            << "-> valmin(as<wide_ft>()  = " << eve::valmin(eve::as<wide_ft>()) << '\n'
            << "-> valmin(as<wide_it>()  = " << eve::valmin(eve::as<wide_it>()) << '\n'
            << "-> valmin(as(x))         = " << eve::valmin(eve::as(x))        << '\n'
            << "-> valmin(as(y))         = " << eve::valmin(eve::as(y))        << '\n';

  float        xf;
  std::int64_t xi;

  std::cout << "---- scalar" << '\n'
            << "-> valmin(as<float>()         = " << eve::valmin(eve::as<float>()) << '\n'
            << "-> valmin(as<std::int16_t>()  = " << eve::valmin(eve::as<std::int16_t>()) << '\n'
            << "-> valmin(as(xf))             = " << eve::valmin(eve::as(xf)) << '\n'
            << "-> valmin(as(xi))             = " << eve::valmin(eve::as(xi)) << '\n';

  return 0;
}
