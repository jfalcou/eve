#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft pf = {1.0f, 0.5f, -3.0f, eve::inf(eve::as<float>())};

  std::cout << "---- simd" << '\n'
            << "<- pf               = " << pf << '\n'
            << "-> rsqrt(pf)        = " << eve::rsqrt(pf) << '\n'
            << "-> raw(rsqrt)(pf)   = " << eve::raw(eve::rsqrt)(pf) << '\n'
            ;

  float xf = 32.768f;

  std::cout << "---- scalar" << '\n'
            << "<- xf               = " << xf << '\n'
            << "-> sqrt(xf)         = " << eve::rsqrt(xf) << '\n';

  return 0;
}
