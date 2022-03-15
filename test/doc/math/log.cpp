#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{
  wide_ft pf = {0.0f, -0.0f, -1.0f, 1.0f, 2.0f,
               eve::inf(eve::as<float>()), 4.0f, eve::nan(eve::as<float>())};

  std::cout << "---- simd" << '\n'
            << "<- pf            = " << pf << '\n'
            << "-> diff(log)(pf) = " << eve::diff(eve::log)(pf) << '\n'
            << "-> log(pf)       = " << eve::log(pf) << '\n';

  float xf = 1.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf      = " << xf << '\n'
            << "-> log(xf) = " << eve::log(xf) << '\n';
  return 0;
}
