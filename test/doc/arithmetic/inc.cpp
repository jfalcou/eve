//#include <eve/function/inc.hpp>
#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <eve/module/core/constant/inf.hpp>
#include <eve/module/core/constant/minf.hpp>
#include <eve/module/core/constant/nan.hpp>
#include <eve/module/core/constant/mindenormal.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft pf = {0.0f, 1.0f, -1.0f, -2.0f};

  std::cout << "---- simd" << '\n'
            << "<- pf           = " << pf << '\n'
            << "-> eve::inc(pf) = " << eve::inc(pf) << '\n';

  float xf = 1.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf           = " << xf << '\n'
            << "-> eve::inc(xf) = " << eve::inc(xf) << '\n';

  return 0;
}
