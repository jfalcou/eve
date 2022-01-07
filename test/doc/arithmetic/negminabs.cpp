#include <eve/function/negminabs.hpp>
#include <eve/function/pedantic/negminabs.hpp>
#include <eve/function/numeric/negminabs.hpp>
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
            << "-> negminabs(pf, qf)            = " << eve::negminabs(pf, qf) << '\n'
            << "-> pedantic(negminabs)(pf, qf) = " << eve::pedantic(eve::negminabs)(pf, qf) << '\n'
            << "-> numeric(negminabs)(pf, qf)  = " << eve::numeric(eve::negminabs)(pf, qf) << '\n';

  float xf = -4.0f;
  float yf = 1.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf                        = " << xf << '\n'
            << "<- yf                        = " << yf << '\n'
            << "-> negminabs(xf, yf)            = " << eve::negminabs(xf, yf) << '\n'
            << "-> pedantic(negminabs)(xf, yf) = " << eve::pedantic(eve::negminabs)(xf, yf) << '\n'
            << "-> numeric(negminabs)(xf, yf)  = " << eve::numeric(eve::negminabs)(xf, yf) << '\n';
   return 0;
}
