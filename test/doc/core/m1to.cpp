//#include <eve/function/m1to.hpp>
#include <eve/module/core.hpp>
#include <eve/function/saturated/m1to.hpp>
#include <eve/wide.hpp>
#include <eve/module/core/constant/inf.hpp>
#include <eve/module/core/constant/minf.hpp>
#include <eve/module/core/constant/nan.hpp>
#include <eve/module/core/constant/mindenormal.hpp>
#include <iostream>

using wide_it = eve::wide <std::int16_t, eve::fixed<8>>;

int main()
{
  wide_it pi = { 0, 1, 2, 3, -1, -32766, -32767, -32768};

  std::cout
    << "---- simd" << '\n'
    << "<- pi                       = " << pi << '\n'
    << "-> m1to(pi)             = " << eve::m1to(pi) << '\n'
    << "-> saturated(m1to(pi)) = " << eve::saturated(eve::m1to)(pi) << '\n';


  float xf = 2.0f;

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf                       = " << xf << '\n'
    << "-> m1to(xf)             = " << eve::m1to(xf) << '\n';

  return 0;
}
