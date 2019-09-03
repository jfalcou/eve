#include <eve/function/arg.hpp>
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
                -1.0f,
                -2.0f,
                eve::Mindenormal<float>(),
                eve::Inf<float>(),
                eve::Minf<float>(),
                eve::Nan<float>()};

  std::cout << "---- simd" << '\n'
            << "<- pf =                      " << pf << '\n'
            << "-> eve::arg(pf) =            " << eve::arg(pf) << '\n'
            << "-> eve::pedantic_(eve::arg)(pf) = " << eve::pedantic_(eve::arg)(pf) << '\n';

  float xf = 1.0f;
  float yf = eve::Nan<float>();

  std::cout << "---- scalar" << '\n'
            << "<- xf =                      " << xf << '\n'
            << "-> eve::arg(xf) =            " << eve::arg(xf) << '\n'
            << "<- yf =                      " << yf << '\n'
            << "-> eve::arg(yf) =            " << eve::arg(yf) << '\n'
            << "-> eve::pedantic_(eve::arg)(yf) = " << eve::pedantic_(eve::arg)(yf) << '\n';
  return 0;
}
