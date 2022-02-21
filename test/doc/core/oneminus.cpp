#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_it = eve::wide <std::int16_t, eve::fixed<8>>;
using wide_ft = eve::wide <float, eve::fixed<8>>;

int main()
{
  wide_it pi = { 0, 1, 2, 3, -1, -32766, -32767, -32768};
  wide_ft pf = { 0.2, 1, 2.4, 3, -1, -3.7, -327.67, -32768.4};

  std::cout
    << "---- simd" << '\n'
    << "<- pi                       = " << pi << '\n'
    << "-> oneminus(pi)             = " << eve::oneminus(pi) << '\n'
    << "-> saturated(oneminus(pi))  = " << eve::saturated(eve::oneminus)(pi) << '\n'
    << "-> oneminus(pf))            = " << eve::oneminus(pf) << '\n'
    << "-> diff(oneminus)(pf))      = " << eve::diff(eve::oneminus)(pf) << '\n';

  float xf = 2.0f;

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf                       = " << xf << '\n'
    << "-> oneminus(xf)             = " << eve::oneminus(xf) << '\n';

  return 0;
}
