//#include <eve/function/manhattan.hpp>
#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft pf = {-1.0f, 2.0f, -3.0f, -32768.0f};
  wide_ft qf = {-4, 3, -2, -12};

  std::cout << "---- simd" << '\n'
            << "<- pf                     = " << pf << '\n'
            << "<- qf                     = " << qf << '\n'
            << "-> eve::manhattan(pf, qf) = " << eve::manhattan(pf, qf) << '\n';

  float        xf = -32768.0f;
  float        yf = 2.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf                     = " << xf << '\n'
            << "<- yf                     = " << yf << '\n'
            << "-> eve::manhattan(xf, yf) = " << eve::manhattan(xf, yf) << '\n';
  return 0;
}
