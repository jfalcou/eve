#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;

int main()
{
  wide_ft pf( [](auto i, auto) { return 1.2345678+i; } );

  std::cout << "---- simd" << '\n'
            << " <- pf                              = " << pf << '\n'
            << " -> roundscale(pf, 4)               = " << eve::roundscale(pf, 4) << '\n'
            << " -> roundscale[downward2  ](pf, 4)  = " << eve::roundscale[eve::downward2  ](pf, 4) << '\n'
            << " -> roundscale[upward2    ](pf, 4)  = " << eve::roundscale[eve::upward2    ](pf, 4) << '\n'
            << " -> roundscale[to_nearest2](pf, 4)  = " << eve::roundscale[eve::to_nearest2](pf, 4) << '\n'
            << " -> roundscale[toward_zero2](pf, 4) = " << eve::roundscale[eve::toward_zero2](pf, 4) << '\n'   ;

 constexpr eve::index_t<4> four;

  std::cout << "---- simd" << '\n'
            << " <- pf                                 = " << pf << '\n'
            << " -> roundscale(pf, four)               = " << eve::roundscale(pf, four) << '\n'
            << " -> roundscale[downward2  ](pf, four)  = " << eve::roundscale[eve::downward2  ](pf, four) << '\n'
            << " -> roundscale[upward2    ](pf, four)  = " << eve::roundscale[eve::upward2    ](pf, four) << '\n'
            << " -> roundscale[to_nearest2](pf, four)  = " << eve::roundscale[eve::to_nearest2](pf, four) << '\n'
            << " -> roundscale[toward_zero2](pf, four) = " << eve::roundscale[eve::toward_zero2](pf, four) << '\n'   ;

  float xf = 0x1.fffffep0f;

  std::cout << "---- scalar" << '\n'
                << "<- xf                             = " << std::hexfloat << xf << '\n';
    for (int i = 0;  i < 16; ++i)
      std::cout << "-> roundscale[toward_zero](xf," << std::setw(2) << i << ")  = " << std::hexfloat << eve::roundscale[eve::toward_zero](xf, i) << '\n';
  return 0;
}
