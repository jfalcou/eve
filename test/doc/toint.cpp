#include <eve/function/toint.hpp> 
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
            << "-> eve::toint(pf) =            " << eve::toint(pf) << '\n'
            << "-> eve::pedantic_(eve::toint)(pf) = " << eve::pedantic_(eve::toint)(pf) << '\n';

  float xf = 1.0f;
  float yf = eve::Nan<float>();

  std::cout << "---- scalar" << '\n'
            << "<- xf =                      " << xf << '\n'
            << "-> eve::toint(xf) =            " << eve::toint(xf) << '\n'
            << "<- yf =                      " << yf << '\n'
            << "-> eve::toint(yf) =            " << eve::toint(yf) << '\n'
            << "-> eve::pedantic_(eve::toint)(yf) = " << eve::pedantic_(eve::toint)(yf) << '\n';
  return 0;
}
