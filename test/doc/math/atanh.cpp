#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft pf = {1.0f, 0.5f, 0.0, -0.5};

  std::cout << "---- simd" << '\n'
            << "<- pf        = " << pf << '\n'
            << "-> diff(atanh)(pf) = " << eve::diff(eve::atanh)(pf) << '\n'
            << "-> atanh(pf) = " << eve::atanh(pf) << '\n';

  float xf = 1.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf        = " << xf << '\n'
            << "-> atanh(xf) = " << eve::atanh(xf) << '\n';
  return 0;
}
