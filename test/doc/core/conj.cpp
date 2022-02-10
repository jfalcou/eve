//#include <eve/function/conj.hpp>
#include <eve/module/core.hpp>
#include <eve/function/saturated/conj.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft pf = {-1.0f, 2.0f, -3.0f, -32768.0f};

  std::cout << "---- simd" << '\n'
            << "<- pf                   = " << pf << '\n'
            << "-> conj(pf)             = " << eve::conj(pf) << '\n';

  float        xf = -32768.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf                   = " << xf << '\n'
            << "-> conj(xf)             = " << eve::conj(xf) << '\n';
  return 0;
}
