#include <eve/function/sqr_abs.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft pf = {-1.0f, 2.0f, -3.0f, 182.0f};

  std::cout << "---- simd" << '\n'
            << "<- pf          = " << pf << '\n'
            << "-> sqr_abs(pf) = " << eve::sqr_abs(pf) << '\n';

  float        xf = -32768.0f;


  std::cout << "---- scalar" << '\n'
            << "<- xf          = " << xf << '\n'
            << "-> sqr_abs(xf) = " << eve::sqr_abs(xf) << '\n';
  return 0;
}
