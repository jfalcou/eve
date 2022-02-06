#include <eve/function/exponentbits.hpp>
#include <eve/wide.hpp>
#include <eve/module/core/constant/inf.hpp>
#include <eve/module/core/constant/minf.hpp>
#include <eve/module/core/constant/nan.hpp>
#include <eve/module/core/constant/mindenormal.hpp>
#include <iostream>

using wide_ft = eve::wide<double, eve::fixed<8>>;

int main()
{

  wide_ft pf = {0.0f,
                1.0f,
                -1.0f,
                -2.0f,
                eve::mindenormal(eve::as<float>()),
                eve::inf(eve::as<float>()),
                eve::minf(eve::as<float>()),
                eve::nan(eve::as<float>())};

  std::cout << "---- simd" << '\n'
            << "<- pf =                      " << pf << '\n'
            << "-> eve::exponentbits(pf) =   " << std::hex << eve::exponentbits(pf) << '\n';

  float xf = 1.0f;
  float yf = eve::nan(eve::as<float>());

  std::cout << "---- scalar" << '\n'
            << "<- xf =                      " << std::dec << xf << '\n'
            << "-> eve::exponentbits(xf) =   " << std::hex << eve::exponentbits(xf) << '\n'
            << "<- yf =                      " << std::dec << yf << '\n'
            << "-> eve::exponentbits(yf) =   " << std::hex << eve::exponentbits(yf) << '\n';
  return 0;
}
