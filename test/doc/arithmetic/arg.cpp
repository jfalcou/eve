//#include <eve/function/arg.hpp>
#include <eve/module/arithmetic.hpp>
#include <eve/function/pedantic/arg.hpp>
#include <eve/wide.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{
  using eve::pedantic;

wide_ft pf = {0.0f, -0.0f, -1.0f, -2.0f, 2.0f,
               eve::inf(eve::as<float>()), eve::minf(eve::as<float>()), eve::nan(eve::as<float>())};

  std::cout << "---- simd" << '\n'
            << "<- pf                      = " << pf << '\n'
            << "-> arg(pf)                 = " << eve::arg(pf) << '\n'
            << "-> pedantic(eve::arg)(pf)  = " << eve::pedantic(eve::arg)(pf) << '\n';

  float xf = 1.0f;
  float yf = eve::nan(eve::as<float>());

  std::cout << "---- scalar" << '\n'
            << "<- xf                      = " << xf << '\n'
            << "-> arg(xf)                 = " << eve::arg(xf) << '\n'
            << "<- yf                      = " << yf << '\n'
            << "-> arg(yf)                 = " << eve::arg(yf) << '\n'
            << "-> pedantic(eve::arg)(yf)  = " << eve::pedantic(eve::arg)(yf) << '\n';
  return 0;
}
