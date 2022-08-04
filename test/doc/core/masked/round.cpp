#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{
  wide_ft pf = {-1.0f, -1.3f, -1.5f, -1.7f, 2.0f, 2.3f, 2.5f, 2.7f};

  std::cout << "---- simd" << '\n'
            << "<- pf                               = " << pf << '\n'
            << "-> round[pf>-1.4f](pf)              = " << eve::round[pf>-1.4f](pf) << '\n'
            << "-> upward(round[pf>-1.4f])(pf)      = " << eve::upward(eve::round[pf>-1.4f])(pf) << '\n'
            << "-> downward(round[pf>-1.4f])(pf)    = " << eve::downward(eve::round[pf>-1.4f])(pf) << '\n'
            << "-> to_nearest(round[pf>-1.4f])(pf)  = " << eve::to_nearest(eve::round[pf>-1.4f])(pf) << '\n'
            << "-> toward_zero(round[pf>-1.4f])(pf) = " << eve::toward_zero(eve::round[pf>-1.4f])(pf) << '\n';
  return 0;
}
