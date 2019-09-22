#include <eve/function/quadrant.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;
using wide_it = eve::wide<int16_t, eve::fixed<8>>;

int main()
{
  wide_ft pf  = {0.0f, 1.0f, 2.0f, 3.0f, -3.0f, -2.0f, -1.0f, -0.0f  }; 

  std::cout << "---- simd" << '\n'
            << "<- pf =                  " << pf << '\n'
            << "-> eve::quadrant(pf) = " << eve::quadrant(pf) << '\n'; 

  float   xf = 15.0f;
  int32_t yf = 29; 

  std::cout << "---- scalar" << '\n'
            << "<- xf =                  " << xf << '\n'
            << "-> eve::quadrant(xf) = " << eve::quadrant(xf) << '\n'
            << "<- yf =                  " << yf << '\n'
            << "-> eve::quadrant(yf) = " << eve::quadrant(yf) << '\n';
  return 0;
}
