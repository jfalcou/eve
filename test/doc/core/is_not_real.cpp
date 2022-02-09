//#include <eve/function/is_not_real.hpp>
#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft pf = {0.0f, 1.0f, -0.0f, -2.0f};

  std::cout << "---- simd" << '\n'
            << "<- pf              = " << pf << '\n'
            << "-> is_not_real(pf) = " << eve::is_not_real(pf) << '\n';

  float xf = 1.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf              = " << xf << '\n'
            << "-> is_not_real(xf) = " << eve::is_not_real(xf) << '\n';
  return 0;
}
