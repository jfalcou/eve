//#include <eve/function/iround.hpp>
#include <eve/module/arithmetic.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{
  wide_ft pf = {-1.0f, -1.3f, -1.5f, -1.7f, 2.0f, 2.3f, 2.5f, 2.7f};

  std::cout << "---- simd" << '\n'
            << "<- pf                       = " << pf << '\n'
            << "-> iround(pf)               = " << eve::iround(pf) << '\n'
            << "-> upward(iround)(pf)      = " << eve::upward(eve::iround)(pf) << '\n'
            << "-> downward(iround)(pf)    = " << eve::downward(eve::iround)(pf) << '\n'
            << "-> to_nearest(iround)(pf)  = " << eve::to_nearest(eve::iround)(pf) << '\n'
            << "-> toward_zero(iround)(pf) = " << eve::toward_zero(eve::iround)(pf) << '\n';

  float xf = -32.768f;

  std::cout << "---- scalar" << '\n'
            << "<- xf                       = " << xf << '\n'
            << "-> iround(xf)               = " << eve::iround(xf) << '\n'
            << "-> upward(iround)(xf)      = " << eve::upward(eve::iround)(xf) << '\n'
            << "-> downward(iround)(xf)    = " << eve::downward(eve::iround)(xf) << '\n'
            << "-> to_nearest(iround)(xf)  = " << eve::to_nearest(eve::iround)(xf) << '\n'
            << "-> toward_zero(iround)(xf) = " << eve::toward_zero(eve::iround)(xf) << '\n';
  return 0;
}
