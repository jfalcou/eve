#include <eve/function/atand.hpp>
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

  std::cout
    << "---- simd" << '\n'
    << "<- pf =                      " << pf << '\n'
    << "-> eve::atand(pf) =          " << eve::atand(pf) << '\n'; 

  float xf = 1.0f;
  float yf = 0.0f;

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf =                      " << xf << '\n'
    << "-> eve::atand(xf) =            " << eve::atand(xf) << '\n'
    << "<- yf =                      " << yf << '\n'
    << "-> eve::atand(yf) =            " << eve::atand(yf) << '\n'; 
  return 0;
}
