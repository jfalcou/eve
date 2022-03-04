#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft pf = {1.0f, 0.0f, eve::inf(eve::as<float>()), eve::nan(eve::as<float>())};

  std::cout << "---- simd" << '\n'
            << "<- pf             = " << pf << '\n'
            << "-> tanh(pf)       = " << eve::tanh(pf) << '\n'
            << "-> diff(tanh)(pf) = " << eve::diff(eve::tanh)(pf) << '\n';


  float xf = 3.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf       = " << xf << '\n'
            << "-> tanh(xf) = " << eve::tanh(xf) << '\n';
  return 0;
}
