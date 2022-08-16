#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<8>>;

int main()
{
  wide_ft pf = { 0.0f, 1.0f, -1.0f, 90.0f
                 ,180.0f, eve::inf(eve::as<float>()), eve::minf(eve::as<float>()), eve::nan(eve::as<float>()) };

  std::cout
    << "---- simd" << '\n'
    << "<- pf                = " << pf << '\n'
    << "-> eve::deginrad(pf)  = " << eve::deginrad(pf) << '\n';

  float xf = 45.0f;
  float yf = eve::pi(eve::as<float>());

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf =                  " << xf << '\n'
    << "-> eve::deginrad(xf) =      " << eve::deginrad(xf) << '\n'
    << "<- yf =                  " << yf << '\n'
    << "-> eve::deginrad(yf) =      " << eve::deginrad(yf) << '\n';
  return 0;
}
