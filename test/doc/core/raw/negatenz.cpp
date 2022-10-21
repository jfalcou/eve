#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{
  wide_ft pf = {0.0f, -0.0f, 0.0f, -0.0f, 2.0f, -2.0f,  2.0f, 2.0f};
  wide_ft qf = {4.0f, 4.0f, -4.0f,  -4.0, 4.0f, 4.0f, -0.0f,  +0.0f};

  std::cout << "---- simd" << '\n'
            << "<- pf                       = " << pf << '\n'
            << "<- qf                       = " << qf << '\n'
            << "-> raw(negatenz)(pf, qf)    = " << eve::raw(negatenz)(pf, qf) << '\n';

  float xf = 4.0f;
  float yf = -1.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf                    = " << xf << '\n'
            << "<- yf                    = " << yf << '\n'
            << "-> raw(negatenz)(xf, yf) = " << eve::raw(negatenz)(xf, yf) << '\n';
  return 0;
}
