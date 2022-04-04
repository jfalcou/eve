#include <eve/module/ad.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft  = eve::wide<float, eve::fixed<4>>;
using wide_vdt = eve::wide<eve::valder<float>, eve::fixed<4>>;
using vd_t     = eve::valder<double>;

int main()
{
  wide_ft x   = {-1.0f, 2.0f, -3.0f,  0.0f};
  wide_ft y   = { 1.0f, 4.5f, -1.0f,  2.3f};
  wide_vdt vx(eve::var(x));

  std::cout << "---- simd" << '\n'
            << "<- x                 = " << x << '\n'
            << "<- vx                = " << vx << '\n'
            << "-> hypot(vx, 1.0f)   = " << eve::hypot(vx, 1.0f) << '\n'
            << "-> hypot(x, y, y)   = " << eve::hypot(x, y, y) << '\n'
            << "-> hypot(vx, y, y)   = " << eve::hypot(vx, y, y) << '\n'
//            << "-> pedantic(hypot)(vx, y, y)   = " << eve::pedantic(eve::hypot)(vx, y, y) << '\n'
    ;

  vd_t sx(eve::var(-2.4));

  std::cout << "---- scalar" << '\n'
            << "<- sx        = " << sx << '\n'
            << "-> hypot(sx)   = " << eve::hypot(sx, 1.0) << '\n';
  return 0;
}
