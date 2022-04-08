#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/module/ad.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;
using wide_vdt = eve::wide<eve::valder<float>, eve::fixed<4>>;
using vd_t     = eve::valder<float>;

int main()
{
  auto f = [](auto x, auto y,  auto z){return eve::fma(x, y, z); };
  wide_ft x = {3, 4, 5, 6};
  wide_ft y = {1, 2, 3, 4};
  wide_ft z = {5, 6, 7, 8};
  wide_ft dx = {1.0, 0.5, 0.1, 0.2};
  wide_ft dy = {0.0, 1.0, -3.0, 2.0};
  wide_ft dz = {1.0, 2.0, -1.0, 2.0};
  auto zz = eve::differential(f, x, y, z);
  auto v = eve::var(x);
  std::cout << v             << '\n' ;
  std::cout << "---- scalar" << '\n'
            << "<- x                                   = " << x << '\n'
            << "<- y                                   = " << y << '\n'
            << "<- z                                   = " << z << '\n'
            << "<- differential(f, x, y, z)(dx, dy, dz) = "  <<     zz(dx, dy, dz) << '\n'
            << "<- der(f(v, y, z)) = " << eve::der(f(v, y, z)) << '\n'
    ;
  return 0;
}
