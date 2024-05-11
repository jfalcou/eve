#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft pf( [](auto i, auto) { return 1.2345678+i; } );

  std::cout << "---- simd" << '\n'
            << " <- pf            = " << pf << '\n'
            << " -> roundscale(pf, 4)              = " << eve::roundscale(pf, 4) << '\n'
            << " -> roundscale(pf, 4)              = " << eve::roundscale(pf, 4) << '\n'
            << " -> upward(roundscale)(pf, 4)      = " << eve::roundscale[eve::downward  ](pf, 4) << '\n'
            << " -> downward(roundscale)(pf, 4)    = " << eve::roundscale[eve::upward    ](pf, 4) << '\n'
            << " -> to_nearest(roundscale)(pf, 4)  = " << eve::roundscale[eve::to_nearest](pf, 4) << '\n';

  float xf = 0x1.fffffep0f;

  std::cout << "---- scalar" << '\n'
                << "<- xf                             = " << std::hexfloat << xf << '\n';
    for (int i = 0;  i < 16; ++i)
      std::cout << "-> roundscale[toward_zero](xf," << std::setw(2) << i << ")  = " << std::hexfloat << eve::roundscale[eve::toward_zero](xf, i) << '\n';
  return 0;
}
