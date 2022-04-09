#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/module/ad.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;
using wide_vdt = eve::wide<eve::valder<float>, eve::fixed<4>>;


int main()
{
  wide_ft x = {3, 4, 5, 6};
  wide_ft y = {1, 2, 3, 4};
  wide_ft z = {5, 6, 7, 8};
  std::cout << "---- scalar" << '\n'
            << "<- x                                    = " << x << '\n'
            << "<- y                                    = " << y << '\n'
            << "<- z                                    = " << z << '\n'
            << "<- eve::geommean(x, y)                  = " << eve::geommean(x, y) << '\n'
            << "-> val(eve::geommean(var(x), y))        = " << eve::val(eve::geommean(eve::var(x), y)) << '\n'
            << "-> der(eve::geommean(x, var(y)))        = " << eve::der(eve::geommean(x, eve::var(y))) << '\n'
            << "-> der(eve::geommean(var(x), y))        = " << eve::der(eve::geommean(eve::var(x), y)) << '\n'
            << "<- eve::geommean(x, y, z)               = " << eve::geommean(x, y, z) << '\n';
  return 0;
}
