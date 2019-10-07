#include <eve/function/exponentbits.hpp>
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
            << "-> eve::exponentbits(pf) =            " << eve::exponentbits(pf) << '\n'
            << "-> eve::pedantic_(eve::exponentbits)(pf) = " << eve::pedantic_(eve::exponentbits)(pf) << '\n';

  float xf = 1.0f;
  float yf = eve::Nan<float>();

  std::cout << "---- scalar" << '\n'
            << "<- xf =                      " << xf << '\n'
            << "-> eve::exponentbits(xf) =            " << eve::exponentbits(xf) << '\n'
            << "<- yf =                      " << yf << '\n'
            << "-> eve::exponentbits(yf) =            " << eve::exponentbits(yf) << '\n'
            << "-> eve::pedantic_(eve::exponentbits)(yf) = " << eve::pedantic_(eve::exponentbits)(yf) << '\n';
  return 0;
}
