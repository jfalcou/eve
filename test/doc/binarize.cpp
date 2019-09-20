#include <eve/function/binarize.hpp>
#include <eve/wide.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/binarizetvalmax.hpp>
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
            << "-> eve::binarize(pf) = " << eve::binarize(pf) << '\n'
            << "<- pi =                  " << pi << '\n'
            << "-> eve::binarize(pi) = " << eve::binarize(pi) << '\n'
            << "-> eve::saturated_(eve::binarize)(pi) = " << eve::saturated_(eve::binarize)(pi) << '\n';

  float   xf = 1.0f;
  int32_t yf = eve::Sqrtvalmax<int32_t>() + 10;

  std::cout << "---- scalar" << '\n'
            << "<- xf =                  " << xf << '\n'
            << "-> eve::binarize(xf) = " << eve::binarize(xf) << '\n'
            << "<- yf =                  " << yf << '\n'
            << "-> eve::binarize(yf) = " << eve::binarize(yf) << '\n';
  return 0;
}
