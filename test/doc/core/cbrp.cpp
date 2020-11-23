#include <eve/function/cbrp.hpp>
#include <eve/constant/inf.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_t = eve::wide<float, eve::fixed<8>>;

int main()
{
  wide_t a =  {3,   3,   2,    -3,   4,   4,   4,   eve::inf(eve::as<float>())};
  wide_t ap = {0,   2,   3,    -2,   6,   6,   6,   eve::inf(eve::as<float>())};
  wide_t b =  {3,   3,   2,    -3,   4,   4,   4,   eve::inf(eve::as<float>())};
  wide_t bp = {0,   -2,   3,    -2,   6,   6,   6,   eve::inf(eve::as<float>())};
  wide_t t =  {0.2, 0.8, 0.2,  0.5,  0.0, 1.0, 2.0, 0.5};

  std::cout << "---- simd" << '\n'
            << " <- a                              = " << a << '\n'
            << " <- ap                             = " << ap << '\n'
            << " <- b                              = " << b << '\n'
            << " <- bp                             = " << bp << '\n'
            << " <- t                              = " << t << '\n'
            << " -> pedantc(cbrp)(a, ap, b, bp, t) = " << eve::pedantic(eve::cbrp)(a, ap, b, bp, t) << '\n'
            << " -> cbrp(a, ap, b, bp, t)          = " << eve::cbrp(a, ap, b, bp, t) << '\n';

  float x = 1.0, y = 2.0, xp = 1.0, yp = -1.0, ts = 0.1;

  std::cout << "---- scalar" << '\n'
            << " <- x                              = " << x << '\n'
            << " <- xp                             = " << xp << '\n'
            << " <- y                              = " << y << '\n'
            << " <- yp                             = " << yp << '\n'
            << " <- t                              = " << ts << '\n'
            << " -> cbrp(x, xp, y, yp, ts)         = " << eve::cbrp(x, xp, y, yp, ts) << '\n';

  return 0;
}
