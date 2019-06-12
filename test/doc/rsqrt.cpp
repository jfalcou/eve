#include <eve/function/rsqrt.hpp>
#include <eve/wide.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/rsqrtvalmax.hpp>
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<8>>;
using wide_it = eve::wide <int16_t, eve::fixed<8>>;

int main()
{
  wide_ft pf = { 0.0f, 1.0f, 4.0f, -2.0f
                , eve::Sqrtvalmax<float>(), eve::Inf<float>(), eve::Minf<float>(), eve::Nan<float>() };
  int16_t svm =  eve::Sqrtvalmax<int16_t>(); 
  wide_it pi = { 0, 1, 4, 2, svm-1, svm, svm+1, svm+2 };

  std::cout
    << "---- simd" << '\n'
    << "<- pf =                  " << pf << '\n'
    << "-> eve::rsqrt(pf) = " << eve::rsqrt(pf) << '\n'
    << "<- pi =                  " << pi << '\n'
    << "-> eve::rsqrt(pi) = " << eve::rsqrt(pi) << '\n';

  float xf = 1.0f;
  int32_t yf = eve::Sqrtvalmax<int32_t>()+10;

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf =                  " << xf << '\n'
    << "-> eve::rsqrt(xf) = " << eve::rsqrt(xf) << '\n'
    << "<- yf =                  " << yf << '\n'
    << "-> eve::rsqrt(yf) = " << eve::rsqrt(yf) << '\n';
  return 0;
}
