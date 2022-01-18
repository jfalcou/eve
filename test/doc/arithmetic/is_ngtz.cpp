//#include <eve/function/is_ngtz.hpp>
#include <eve/module/ieee.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft pf = {0.0f, 1.0f, -1.0f, -0.0f};

  std::cout << "---- simd" << '\n'
            << "<- pf =          " << pf << '\n'
            << "-> is_ngtz(pf) = " << eve::is_ngtz(pf) << '\n';

  float xf = 1.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf          = " << xf << '\n'
            << "-> is_ngtz(xf) = " << eve::is_ngtz(xf) << '\n';
  return 0;
}
