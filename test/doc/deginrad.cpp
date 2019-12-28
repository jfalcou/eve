#include <eve/function/deginrad.hpp>
#include <eve/wide.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/pi.hpp>
#include <eve/constant/pio_2.hpp> 
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<8>>;

int main()
{
  wide_ft pf = { 0.0f, 1.0f, -1.0f, eve::Pio_2<float>()
                 ,eve::Pi<float>(), eve::Inf<float>(), eve::Minf<float>(), eve::Nan<float>() };

  std::cout
    << "---- simd" << '\n'
    << "<- pf =                  " << pf << '\n'
    << "-> eve::deginrad(pf) =      " << eve::deginrad(pf) << '\n';

  float xf = 1.0f;
  float yf = eve::Pi<float>();

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf =                  " << xf << '\n'
    << "-> eve::deginrad(xf) =      " << eve::deginrad(xf) << '\n'
    << "<- yf =                  " << yf << '\n'
    << "-> eve::deginrad(yf) =      " << eve::deginrad(yf) << '\n';
  return 0;
}
