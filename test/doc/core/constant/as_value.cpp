#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;
using wide_dt = eve::wide<double, eve::fixed<4>>;
using wide_it = eve::wide<int16_t, eve::fixed<4>>;

int main()
{
  wide_dt pf = {-1.0f, 2.0f, eve::inf(eve::as<double>()), eve::valmax(eve::as<double>())};

  std::cout << "---- simd" << '\n'
            << "<- pf                  = " << pf << '\n'
//            << "<- as_value(pf, as<wide_ft>())  = " << eve::as_value(pf, eve::as<wide_ft>()) << '\n'
            << "<- as_value(valmax, as<wide_it>())  = " << eve::as_value(eve::valmax, eve::as<wide_it>()) << '\n';

  double        xf = -62768.0f;

  std::cout << "---- scalar" << '\n'
            << "<- as_value(xf, as<float>())  = " << eve::as_value(xf, eve::as<float>()) << '\n'
            << "<- as_value(xf, as<int16_t>())  = " << eve::as_value(xf, eve::as<int16_t>()) << '\n';
;
  return 0;
}
