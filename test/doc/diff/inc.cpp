#include <eve/function/diff/inc.hpp>
#include <eve/wide.hpp>
#include <eve/module/core/constant/inf.hpp>
#include <eve/module/core/constant/minf.hpp>
#include <eve/module/core/constant/nan.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{
  wide_ft pf = {0.0f, 1.0f, -2.0f, 10.0f, 200.0f, -1000.0f,
               eve::inf(eve::as<float>()), eve::nan(eve::as<float>())};

  std::cout << "---- simd" << '\n'
            << "<- pf                                = " << pf << '\n'
            << "-> eve::diff(eve::inc)(pf)     = " << eve::diff(eve::inc)(pf) << '\n'
            << "-> eve::diff(eve::inc)(pf, 2u) = " << eve::diff(eve::inc)(pf, 2u) << '\n'
            << "-> eve::diff(eve::inc)(pf, 3u) = " << eve::diff(eve::inc)(pf, 3u) << '\n';

  float xf = 1.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf                            = " << xf << '\n'
            << "-> eve::diff(eve::inc)(xf) = " << eve::diff(eve::inc)(xf) << '\n';
  return 0;
}
