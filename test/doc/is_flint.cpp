#include <eve/function/is_flint.hpp>
#include <eve/wide.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/valmax.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{
  wide_ft pf = {0.0f,
                1.5f,
                -1.0f,
                -2.0f,
                eve::Valmax<float>(),
                eve::Inf<float>(),
                eve::Minf<float>(),
                eve::Nan<float>()};

  std::cout << "---- simd" << '\n'
            << "<- pf =                  " << pf << '\n'
            << "-> eve::is_flint(pf) = " << eve::is_flint(pf) << '\n';

  float xf = 1.001f;
  float yf = eve::Valmax<float>();

  std::cout << "---- scalar" << '\n'
            << "<- xf =                  " << xf << '\n'
            << "-> eve::is_flint(xf) = " << eve::is_flint(xf) << '\n'
            << "<- yf =                  " << yf << '\n'
            << "-> eve::is_flint(yf) = " << eve::is_flint(yf) << '\n';
  return 0;
}
