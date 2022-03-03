#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{
  wide_ft pf = {-1.0f, -1.3f, -1.5f, -1.7f, 2.0f, 2.3f, 2.5f, 2.7f};

  std::cout << "---- simd" << '\n'
            << "<- pf                      = " << pf << '\n'
            << "-> round(pf)               = " << eve::round(pf) << '\n'
            << "-> upward(round)(pf)      = " << eve::upward(eve::round)(pf) << '\n'
            << "-> downward(round)(pf)    = " << eve::downward(eve::round)(pf) << '\n'
            << "-> to_nearest(round)(pf)  = " << eve::to_nearest(eve::round)(pf) << '\n'
            << "-> toward_zero(round)(pf) = " << eve::toward_zero(eve::round)(pf) << '\n';

  float xf = -32.768f;

  std::cout << "---- scalar" << '\n'
            << "<- xf                      = " << xf << '\n'
            << "-> round(xf)               = " << eve::round(xf) << '\n'
            << "-> upward(round)(xf)      = " << eve::upward(eve::round)(xf) << '\n'
            << "-> downward(round)(xf)    = " << eve::downward(eve::round)(xf) << '\n'
            << "-> to_nearest(round)(xf)  = " << eve::to_nearest(eve::round)(xf) << '\n'
            << "-> toward_zero(round)(xf) = " << eve::toward_zero(eve::round)(xf) << '\n';
  return 0;
}
