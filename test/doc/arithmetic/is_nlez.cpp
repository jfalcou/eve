//#include <eve/function/is_nlez.hpp>
#include <eve/module/ieee.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft pf = {0.0f, 1.0f, -1.0f, -0.0f};

  std::cout << "---- simd" << '\n'
            << "<- pf          = " << pf << '\n'
            << "-> is_nlez(pf) = " << eve::is_nlez(pf) << '\n';

  float xf = 1.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf          = " << xf << '\n'
            << "-> is_nlez(xf) = " << eve::is_nlez(xf) << '\n';
  return 0;
}
