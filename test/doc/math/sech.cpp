#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft pf = {1.0f, 0.0f, eve::inf(eve::as<float>()), eve::nan(eve::as<float>())};

  std::cout << "---- simd" << '\n'
            << "<- pf             = " << pf << '\n'
            << "-> sech(pf)       = " << eve::sech(pf) << '\n'
            << "-> diff(sech)(pf) = " << eve::diff(eve::sech)(pf) << '\n';

  float xf = 3.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf       = " << xf << '\n'
            << "-> sech(xf) = " << eve::sech(xf) << '\n';
  return 0;
}
