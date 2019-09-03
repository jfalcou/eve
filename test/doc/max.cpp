#include <eve/function/max.hpp>
#include <eve/wide.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/mindenormal.hpp>
#include <eve/tags.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;
using eve::pedantic_;

int main()
{
  wide_ft pf = {0.0f,
                1.0f,
                -1.0f,
                -2.0f,
                eve::Mindenormal<float>(),
                eve::Inf<float>(),
                eve::Minf<float>(),
                eve::Nan<float>()};
  wide_ft qf = {eve::Mindenormal<float>(),
                1.0f,
                -1.0f,
                eve::Inf<float>(),
                eve::Minf<float>(),
                eve::Nan<float>(),
                0.0f,
                -2.0f};

  std::cout << "---- simd" << '\n'
            << "<- pf =                          " << pf << '\n'
            << "<- qf =                          " << qf << '\n'
            << "-> eve::max(pf, qf) =            " << eve::max(pf, qf) << '\n'
            << "-> eve::pedantic_(eve::max)(pf, qf) = " << eve::pedantic_(eve::max)(pf, qf) << '\n';

  float xf = 1.0f;
  float yf = eve::Nan<float>();

  std::cout << "---- scalar" << '\n'
            << "<- xf =                          " << xf << '\n'
            << "<- yf =                          " << yf << '\n'
            << "-> eve::max(xf, yf) =            " << eve::max(xf, yf) << '\n'
            << "-> eve::pedantic_(eve::max)(xf, yf) = " << eve::pedantic_(eve::max)(xf, yf) << '\n';
  return 0;
}
