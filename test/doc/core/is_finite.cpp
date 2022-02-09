//#include <eve/function/is_finite.hpp>
#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <eve/module/core/constant/inf.hpp>
#include <eve/module/core/constant/minf.hpp>
#include <eve/module/core/constant/nan.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{
  wide_ft pf = {0.0f, 1.0f, -1.5f, -2.0f, -123.345f,
                eve::inf(eve::as<float>()), eve::minf(eve::as<float>()), eve::nan(eve::as<float>())};

  std::cout << "---- simd" << '\n'
            << "<- pf            = " << pf << '\n'
            << "-> is_finite(pf) = " << eve::is_finite(pf) << '\n';

  float xf = 1.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf            = " << xf << '\n'
            << "-> is_finite(xf) = " << eve::is_finite(xf) << '\n';
  return 0;
}
