#include <eve/module/math.hpp>
#include <eve/function/pedantic/log10.hpp>
#include <eve/wide.hpp>
#include <eve/module/core/constant/inf.hpp>
#include <eve/module/core/constant/nan.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{
  wide_ft pf = {0.0f, -0.0f, -1.0f, 1.0f, 2.0f,
               eve::inf(eve::as<float>()), 10.0f, eve::nan(eve::as<float>())};

  std::cout << "---- simd" << '\n'
            << "<- pf              = " << pf << '\n'
            << "-> log10(pf)       = " << eve::log10(pf) << '\n'
            << "-> diff(log10)(pf) = " << eve::diff(eve::log10)(pf) << '\n';

  float xf = 1.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf        = " << xf << '\n'
            << "-> log10(xf) = " << eve::log10(xf) << '\n';
  return 0;
}
