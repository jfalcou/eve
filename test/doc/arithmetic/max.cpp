//#include <eve/function/max.hpp>
#include <eve/module/arithmetic.hpp>
#include <eve/function/pedantic/max.hpp>
#include <eve/function/numeric/max.hpp>
#include <eve/wide.hpp>
#include <eve/module/core/constant/inf.hpp>
#include <eve/module/core/constant/minf.hpp>
#include <eve/module/core/constant/nan.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;
using eve::pedantic;

int main()
{
  wide_ft pf = {0.0f, 1.0f, -1.0f, -2.0f, 2.0f,
                eve::inf(eve::as<float>()), eve::minf(eve::as<float>()), eve::nan(eve::as<float>())};
  wide_ft qf = {4.0f, 1.0f, -1.0f,  0.0f, eve::nan(eve::as<float>()),
                -0.0f, eve::nan(eve::as<float>()), -2.0f};


  std::cout << "---- simd" << '\n'
            << "<- pf                     = " << pf << '\n'
            << "<- qf                     = " << qf << '\n'
            << "-> max(pf, qf)            = " << eve::max(pf, qf) << '\n'
            << "-> pedantic(max)(pf, qf) = " << eve::pedantic(eve::max)(pf, qf) << '\n'
            << "-> numeric(max)(pf, qf)  = " << eve::numeric(eve::max)(pf, qf) << '\n';

  float xf = 1.0f;
  float yf = eve::nan(eve::as<float>());

  std::cout << "---- scalar" << '\n'
            << "<- xf                     = " << xf << '\n'
            << "<- yf                     = " << yf << '\n'
            << "-> max(xf, yf) =          = " << eve::max(xf, yf) << '\n'
            << "-> pedantic(max)(xf, yf) = " << eve::pedantic(eve::max)(xf, yf) << '\n'
            << "-> numeric(max)(xf, yf)  = " << eve::numeric(eve::max)(xf, yf) << '\n';
  return 0;
}
