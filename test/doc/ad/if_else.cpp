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
  auto inf = eve::inf(eve::as<float>());

  wide_ft x = {-1.0f, 7.5f, inf,  0.1f};
  auto f = [](auto e){return eve::if_else (e < 4, eve::sqr(e), -e);};
  std::cout << "---- scalar" << '\n'
            << "<- x                  = " << x << '\n'
            << "<- f(x)               = " << f(x) << '\n'
            << "-> val(f(var(x)))     = " << eve::val(f(eve::var(x))) << '\n'
            << "-> der(f(var(x)))     = " << eve::der(f(eve::var(x))) << '\n';
  return 0;
}
