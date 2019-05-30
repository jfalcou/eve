#include <eve/function/maxnummag.hpp>
#include <eve/wide.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/mindenormal.hpp>
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<8>>;

int main()
{
  wide_ft pf = { 0.0f, 1.0f, -1.0f, -2.0f
                , eve::Mindenormal<float>(), eve::Inf<float>(), eve::Minf<float>(), eve::Nan<float>() };
  wide_ft qf = { eve::Mindenormal<float>(), 1.0f, -1.0f, eve::Inf<float>(), eve::Minf<float>(), eve::Nan<float>(),
                 0.0f, -2.0f };

  std::cout
    << "---- simd" << '\n'
    << "<- pf =                  " << pf << '\n'
    << "<- qf =                  " << qf << '\n'
    << "-> eve::maxnummag(pf, qf) = " << eve::maxnummag(pf, qf) << '\n';

  float xf = 1.0f;
  float yf = -2.0f;

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf =                  " << xf << '\n'
    << "<- yf =                  " << yf << '\n'
    << "-> eve::maxnummag(xf, yf) = " << eve::maxnummag(xf, yf) << '\n';
  return 0;
}
