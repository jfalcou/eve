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
  wide_ft x = {3, 4, 5, 6};
  wide_ft y = {1, 2, 3, 4};
  wide_ft z = {5, 6, 7, 8};
  std::cout << "---- scalar" << '\n'
            << "<- x                                   = " << x << '\n'
            << "<- y                                   = " << y << '\n'
            << "<- z                                   = " << z << '\n'
            << "<- eve::average(x, y, z)               = " << eve::average(x, y, z) << '\n'
            << "-> val(eve::average(var(x), y, z))     = " << eve::val(eve::average(eve::var(x), y, z)) << '\n'
            << "-> der(eve::average(x, var(y), z))     = " << eve::der(eve::average(x, eve::var(y), z)) << '\n'
            << "-> der(eve::average(x, y, var(z)))     = " << eve::der(eve::average(x, y, eve::var(z))) << '\n'
    ;
  return 0;
}
