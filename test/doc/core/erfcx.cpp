#include <eve/function/erfcx.hpp>
#include <eve/wide.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{

  wide_ft pf = {0.5f, -1.5f, -1.0f, 1.0f, 2.0f,
               eve::inf(eve::as<float>()), eve::minf(eve::as<float>()), eve::nan(eve::as<float>())};

  std::cout << "---- simd" << '\n'
            << "<- pf        = " << pf << '\n'
            << "-> erfcx(pf) = " << eve::erfcx(pf) << '\n';

  float xf = 4.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf        = " << xf << '\n'
            << "-> erfcx(xf) = " << eve::erfcx(xf) << '\n';
  return 0;
}
