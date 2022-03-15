#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{
  wide_ft pf = {0.0f, -0.0f, -1.0f, 1.0f, 2.0f,
               eve::inf(eve::as<float>()), 4.0f, eve::nan(eve::as<float>())};

  std::cout << "---- simd" << '\n'
            << "<- pf             = " << pf << '\n'
            << "-> log2(pf)       = " << eve::log2(pf) << '\n'
            << "-> diff(log2)(pf) = " << eve::diff(eve::log2)(pf) << '\n';

  float xf = 1.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf       = " << xf << '\n'
            << "-> log2(xf) = " << eve::log2(xf) << '\n';
  return 0;
}
