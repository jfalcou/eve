//#include <eve/function/is_ltz.hpp>
#include <eve/module/arithmetic.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft pf = {0.0f, 1.0f, -1.0f, -0.0f};

  std::cout << "---- simd" << '\n'
            << "<- pf         = " << pf << '\n'
            << "-> is_ltz(pf) = " << eve::is_ltz(pf) << '\n';

  float xf = 1.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf         = " << xf << '\n'
            << "-> is_ltz(xf) = " << eve::is_ltz(xf) << '\n';
  return 0;
}
