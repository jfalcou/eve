#include <eve/function/exp2.hpp>
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
            << "-> eve::exp2(pf) =            " << eve::exp2(pf) << '\n'
            << "-> eve::pedantic_(eve::exp2)(pf) = " << eve::pedantic_(eve::exp2)(pf) << '\n';

  float xf = 1.0f;
  float yf = eve::Nan<float>();

  std::cout << "---- scalar" << '\n'
            << "<- xf =                      " << xf << '\n'
            << "-> eve::exp2(xf) =            " << eve::exp2(xf) << '\n'
            << "<- yf =                      " << yf << '\n'
            << "-> eve::exp2(yf) =            " << eve::exp2(yf) << '\n'
            << "-> eve::pedantic_(eve::exp2)(yf) = " << eve::pedantic_(eve::exp2)(yf) << '\n';
  return 0;
}
