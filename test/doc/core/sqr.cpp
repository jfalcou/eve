#include <eve/function/sqr.hpp>
#include <eve/wide.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/sqrtvalmax.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;
using wide_it = eve::wide<int16_t, eve::fixed<8>>;

int main()
{
  wide_ft pf  = {0.0f,
                1.0f,
                -1.0f,
                -2.0f,
                eve::Sqrtvalmax<float>(),
                eve::Inf<float>(),
                eve::Minf<float>(),
                eve::Nan<float>()};
  int16_t svm = eve::Sqrtvalmax<int16_t>();
  wide_it pi  = {0, 1, -1, -2, svm - 1, svm, svm + 1, svm + 2};

  std::cout << "---- simd" << '\n'
            << "<- pf =                  " << pf << '\n'
            << "-> eve::sqr(pf) = " << eve::sqr(pf) << '\n'
            << "<- pi =                  " << pi << '\n'
            << "-> eve::sqr(pi) = " << eve::sqr(pi) << '\n'
            << "-> eve::saturated_(eve::sqr)(pi) = " << eve::saturated_(eve::sqr)(pi) << '\n';

  float   xf = 1.0f;
  int32_t yf = eve::Sqrtvalmax<int32_t>() + 10;

  std::cout << "---- scalar" << '\n'
            << "<- xf =                  " << xf << '\n'
            << "-> eve::sqr(xf) = " << eve::sqr(xf) << '\n'
            << "<- yf =                  " << yf << '\n'
            << "-> eve::sqr(yf) = " << eve::sqr(yf) << '\n';
  return 0;
}
