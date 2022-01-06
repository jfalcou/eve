//#include <eve/function/quadrant.hpp>
#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft pf  = {10.0f, 9.0f, -3.0f, 1.0f};

  std::cout << "---- simd" << '\n'
            << "<- pf          = " << pf << '\n'
            << "->quadrant(pf) = " << eve::quadrant(pf) << '\n';

  float   xf = 15.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf =        = " << xf << '\n'
            << "->quadrant(xf) = " << eve::quadrant(xf) << '\n';
  return 0;
}
