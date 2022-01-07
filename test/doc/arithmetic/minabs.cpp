#include <eve/function/maxmag.hpp>
#include <eve/module/arithmetic.hpp>
#include <eve/function/pedantic/minabs.hpp>
#include <eve/function/numeric/minabs.hpp>
#include <eve/wide.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{
  wide_ft pf = {0.0f, 1.0f,  1.0f, -2.0f, 2.0f,
                eve::inf(eve::as<float>()), eve::minf(eve::as<float>()), eve::nan(eve::as<float>())};
  wide_ft qf = {4.0f, 1.0f, -1.0f,  0.0f,  -3.0f,
                eve::nan(eve::as<float>()),  -eve::nan(eve::as<float>()), -2.0f};

  std::cout << "---- simd" << '\n'
            << "<- pf                        = " << pf << '\n'
            << "<- qf                        = " << qf << '\n'
            << "-> minabs(pf, qf)            = " << eve::minabs(pf, qf) << '\n'
            << "-> pedantic(minabs)(pf, qf) = " << eve::pedantic(eve::minabs)(pf, qf) << '\n'
            << "-> numeric(minabs)(pf, qf)  = " << eve::numeric(eve::minabs)(pf, qf) << '\n';

  float xf = -4.0f;
  float yf = 1.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf                        = " << xf << '\n'
            << "<- yf                        = " << yf << '\n'
            << "-> minabs(xf, yf)            = " << eve::minabs(xf, yf) << '\n'
            << "-> pedantic(minabs)(xf, yf) = " << eve::pedantic(eve::minabs)(xf, yf) << '\n'
            << "-> numeric(minabs)(xf, yf)  = " << eve::numeric(eve::minabs)(xf, yf) << '\n';
   return 0;
}
