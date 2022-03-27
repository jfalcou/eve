#include <eve/module/ad.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft  = eve::wide<float, eve::fixed<4>>;
using wide_vdt = eve::wide<eve::valder<float>, eve::fixed<4>>;
using vd_t     = eve::valder<double>;

int main()
{
  wide_ft x   = {-1.0f, 2.0f, -3.0f,  0.0f};
  wide_ft y   = {-1.0f, 2.0f, -3.0f,  0.0f};
  wide_ft z   = {-1.0f, 2.0f, -3.0f,  0.0f};
  wide_vdt vx(eve::var(x));
  wide_vdt vy(eve::var(y));
  wide_vdt vz(eve::var(z));

  std::cout << "---- simd" << '\n'
            << "<- x              = " << x << '\n'
            << "<- vx             = " << vx << '\n'
            << "<- vy             = " << vx << '\n'
            << "<- vz             = " << vx << '\n'
            << "-> fma(vx, y, z)  = " << eve::fma(vx, y, z) << '\n'
            << "-> fma(x, vy, z) = " << eve::fma(x, vy, z) << '\n'
            << "-> fma(x, y, vz)= " << eve::fma(x, y, vz) << '\n';

  vd_t sx(eve::var(-2.4));

  std::cout << "---- scalar" << '\n'
            << "<- sx                  = " << sx << '\n'
            << "-> fma(sx, 1.0, 3.0)   = " << eve::fma(sx, 1.0, 3.0) << '\n';
  return 0;
}
