//#include <eve/function/is_negative.hpp>
#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <eve/module/core/constant/inf.hpp>
#include <eve/module/core/constant/minf.hpp>
#include <eve/module/core/constant/nan.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{
  wide_ft pf = {0.0f, 1.0f, -1.5f, -2.0f, eve::nan(eve::as<float>()),
                eve::inf(eve::as<float>()), eve::minf(eve::as<float>()), -eve::nan(eve::as<float>())};

  std::cout << "---- simd" << '\n'
            << "<- pf              = " << pf << '\n'
            << "-> is_negative(pf) = " << eve::is_negative(pf) << '\n';

  float xf = 1.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf              = " << xf << '\n'
            << "-> is_negative(xf) = " << eve::is_negative(xf) << '\n';
  return 0;
}
