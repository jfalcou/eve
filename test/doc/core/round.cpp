#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{
  wide_ft pf = {-1.0f, -1.3f, -1.5f, -1.7f, 2.0f, 2.3f, 2.5f, 2.7f};

  std::cout << "---- simd" << '\n'
            << "<- pf                              = " << pf << '\n'
            << "-> round(pf)                       = " << eve::round(pf) << '\n'
            << "-> round[upward     ](pf)          = " << eve::round[eve::upward     ](pf) << '\n'
            << "-> round[downward   ](pf)          = " << eve::round[eve::downward   ](pf) << '\n'
            << "-> round[to_nearest ](pf)          = " << eve::round[eve::to_nearest ](pf) << '\n'
            << "-> round[toward_zero](pf)          = " << eve::round[eve::toward_zero](pf) << '\n'
            << "-> round[pf>-1.4f](pf)             = " << eve::round[pf>-1.4f](pf) << '\n'
            << "-> round[pf>-1.4f][upward     ](pf)= " << eve::round[pf>-1.4f][eve::upward     ](pf) << '\n'
            << "-> round[pf>-1.4f][downward   ](pf)= " << eve::round[pf>-1.4f][eve::downward   ](pf) << '\n'
            << "-> round[pf>-1.4f][to_nearest ](pf)= " << eve::round[pf>-1.4f][eve::to_nearest ](pf) << '\n'
            << "-> round[pf>-1.4f][toward_zero](pf)= " << eve::round[pf>-1.4f][eve::toward_zero](pf) << '\n';

  float xf = -32.768f;

  std::cout << "---- scalar" << '\n'
            << "<- xf                    = " << xf << '\n'
            << "-> round(xf)             = " << eve::round(xf) << '\n'
            << "->round[upward     ](xf) = " << eve::round[eve::upward     ](xf) << '\n'
            << "->round[downward   ](xf) = " << eve::round[eve::downward   ](xf) << '\n'
            << "->round[to_nearest ](xf) = " << eve::round[eve::to_nearest ](xf) << '\n'
            << "->round[toward_zero](xf) = " << eve::round[eve::toward_zero](xf) << '\n';
  return 0;
}
