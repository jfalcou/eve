#include <eve/function/touint.hpp> 
#include <eve/wide.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/mindenormal.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{
  using eve::pedantic_;

  wide_ft pf = {0.0f,
                1.0f,
                1.5f,
                -2.0f,
                eve::Mindenormal<float>(),
                eve::Inf<float>(),
                eve::Minf<float>(),
                eve::Nan<float>()};

  std::cout << "---- simd" << '\n'
            << "<- pf =                              " << pf << '\n'
            << "-> eve::touint(pf) =                 " << eve::touint(pf) << '\n'
            << "-> eve::pedantic_(eve::touint)(pf) = " << eve::pedantic_(eve::touint)(pf) << '\n';

  float xf = 1.0f;
  double yf = 36.5;

  std::cout << "---- scalar" << '\n'
            << "<- xf =                              " << xf << '\n'
            << "-> eve::touint(xf) =                 " << eve::touint(xf) << '\n'
            << "<- yf =                              " << yf << '\n'
            << "-> eve::touint(yf) =                 " << eve::touint(yf) << '\n'
            << "-> eve::pedantic_(eve::touint)(yf) = " << eve::pedantic_(eve::touint)(yf) << '\n';
  return 0;
}
