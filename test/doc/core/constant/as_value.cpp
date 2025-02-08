#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;
using wide_it = eve::wide<int16_t, eve::fixed<4>>;

int main()
{
  std::cout << "---- simd" << '\n'
            << "<- as_value(pf, as<wide_ft>())      = " << eve::as_value(32.5, eve::as<wide_ft>()) << '\n'
            << "<- as_value(valmax, as<wide_it>())  = " << eve::as_value(eve::valmax, eve::as<wide_it>()) << '\n'
    ;

  std::cout << "---- scalar" << '\n'
            << "<- as_value(valmax, as<float>())    = " << eve::as_value(eve::valmax, eve::as<float>()) << '\n';

  return 0;
}
