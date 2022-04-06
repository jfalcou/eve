#include <eve/module/ad.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft  = eve::wide<float, eve::fixed<4>>;
using wide_vdt = eve::wide<eve::valder<float>, eve::fixed<4>>;
using vd_t     = eve::valder<double>;

int main()
{
  wide_ft x   = {-1.0f, 2.0f, -3.0f,  0.0f};
  wide_vdt vx(eve::var(x));
  wide_vdt vy(vx);
  wide_vdt vz =  vx;
  wide_vdt av = eve::average(vx, vy);

  std::cout << "---- simd" << '\n'
            << "<- x            = " << x << '\n'
            << "<- vx           = " << vx << '\n'
            << "-> vy           = " << vy << '\n'
            << "-> vz           = " << vz << '\n'
            << "-> av           = " << av << '\n'
    ;

  vd_t sx(eve::var(-2.4));
  vd_t sy = sx;
  std::cout << "---- scalar" << '\n'
            << "<- sx        = " << sx << '\n'
            << "-> sy        = " << sy << '\n';
  return 0;
}
