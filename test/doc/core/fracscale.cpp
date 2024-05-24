#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;

int main()
{
  wide_ft pf( [](auto i, auto) { return 1.2345678+i; } );

  std::cout << "---- simd" << '\n'
            << " <- pf                            = " << pf << '\n'
            << " -> fracscale(pf, 4)              = " << eve::fracscale(pf, 4) << '\n'
            << " -> fracscale[downward2  ](pf, 4) = " << eve::fracscale[eve::downward2  ](pf, 4) << '\n'
            << " -> fracscale[upward2    ](pf, 4) = " << eve::fracscale[eve::upward2    ](pf, 4) << '\n'
            << " -> fracscale[to_nearest2](pf, 4) = " << eve::fracscale[eve::to_nearest2](pf, 4) << '\n';


  float xf = 0x1.fffffep0f;

  std::cout << "---- scalar" << '\n'
                << "<- xf                             = " << std::hexfloat << xf << '\n';
    for (int i = 0;  i < 20; ++i)
      std::cout << "-> fracscale[toward_zero](xf," << std::setw(2) << i << ")  = " << std::hexfloat << eve::fracscale[eve::toward_zero](xf, i) << '\n';
  return 0;
}
