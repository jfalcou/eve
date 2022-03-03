#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft pf = {0.0f, 1.0f, -1.0f, -2.0f};

  std::cout << "---- simd" << '\n'
            << "<- pf           = " << pf << '\n'
            << "-> dec(pf)       = " << eve::dec(pf) << '\n'
            << "-> diff(dec)(pf) = " << eve::diff(eve::dec)(pf) << '\n'; 

  float xf = 1.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf           = " << xf << '\n'
            << "-> eve::dec(xf) = " << eve::dec(xf) << '\n';

  return 0;
}
