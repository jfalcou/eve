#include <eve/function/nenr.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_t = eve::wide<float, eve::fixed<8>>;

int main()
{
  wide_t oi = {3,   3,   2,    -3,   4,   4,   4,   eve::inf(eve::as<float>())};
  wide_t pi = {2,   2,   3,    -2,   6,   6,   6,   eve::inf(eve::as<float>())};
  wide_t qi = {0.2, 0.8, 0.2,  0.5,  0.0, 1.0, 2.0, 0.5};

  std::cout << "---- simd" << '\n'
            << " <- oi                         = " << oi << '\n'
            << " <- pi                         = " << pi << '\n'
            << " <- qi                         = " << qi << '\n'
            << " -> pedantic(nenr)(oi, pi, qi) = " << eve::pedantic(eve::nenr)(oi, pi, qi) << '\n'
            << " -> numeric(nenr)(oi, pi, qi)  = " << eve::numeric(eve::nenr)(oi, pi, qi) << '\n'
            << " -> nenr(oi, pi, qi)           = " << eve::nenr(oi, pi, qi) << '\n';

  float x = 1.0, y = 2.0, t = 0.1;

  std::cout << "---- scalar" << '\n'
            << " <- x                          = " << x << '\n'
            << " <- y                          = " << y << '\n'
            << " <- t                          = " << t << '\n'
            << " -> nenr(x, y, t)              = " << eve::nenr(x, y, t) << '\n';

  return 0;
}
