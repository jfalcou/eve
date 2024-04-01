#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{
  wide_ft pf = {-1.0f, -1.3f, -1.5f, -1.7f, 2.0f, 2.3f, 2.5f, 2.7f};

  std::cout << "---- simd" << '\n'
            << "<- pf                              = " << pf << '\n'
            << "-> ceil(pf)                        = " << eve::ceil(pf) << '\n'
            << "-> ceil[eve::tolerant]ceil(pf)     = " << eve::ceil[eve::tolerant2](pf) << '\n'
            << "-> ceil[eve::tolerant]ceil(pf, 1)  = " << eve::ceil[eve::tolerant2](pf, 1) << '\n'
            << "-> ceil[pf > -1.5f](pf)            = " << eve::ceil[pf > -1.5f](pf) << '\n';
  float xf = -32.768f;

  std::cout << "---- scalar" << '\n'
            << "<- xf       = " << xf << '\n'
            << "-> ceil(xf) = " << eve::ceil(xf) << '\n';
  return 0;
}
