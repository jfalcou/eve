//#include <eve/function/oneminus.hpp>
#include <eve/module/arithmetic.hpp>
#include <eve/function/saturated/oneminus.hpp>
#include <eve/wide.hpp>
#include <eve/module/core/constant/inf.hpp>
#include <eve/module/core/constant/minf.hpp>
#include <eve/module/core/constant/nan.hpp>
#include <eve/module/arithmetic/constant/mindenormal.hpp>
#include <iostream>

using wide_it = eve::wide <std::int16_t, eve::fixed<8>>;

int main()
{
  wide_it pi = { 0, 1, 2, 3, -1, -32766, -32767, -32768};

  std::cout
    << "---- simd" << '\n'
    << "<- pi                       = " << pi << '\n'
    << "-> oneminus(pi)             = " << eve::oneminus(pi) << '\n'
    << "-> saturated(oneminus(pi)) = " << eve::saturated(eve::oneminus)(pi) << '\n';


  float xf = 2.0f;

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf                       = " << xf << '\n'
    << "-> oneminus(xf)             = " << eve::oneminus(xf) << '\n';

  return 0;
}
