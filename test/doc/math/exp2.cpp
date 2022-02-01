//#include <eve/function/exp2.hpp>
#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <eve/module/core/constant/inf.hpp>
#include <eve/module/core/constant/minf.hpp>
#include <eve/module/core/constant/nan.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;
using wide_it = eve::wide<std::uint32_t, eve::fixed<4>>;

int main()
{

  wide_ft pf = {0.0f, -0.0f, -1.0f, 33.0f, 2.0f,
               eve::inf(eve::as<float>()), eve::minf(eve::as<float>()), eve::nan(eve::as<float>())};
  wide_it pi = {0, 2, 8, 33};

  std::cout << "---- simd" << '\n'
            << "<- pf                  = " << pf << '\n'
            << "<- pi                  = " << pi << '\n'
            << "-> exp2(pf)            = " << eve::exp2(pf) << '\n'
            << "-> exp2(pi)            = " << eve::exp2(pi) << '\n'
            << "-> float32(exp2)(pi)   = " << eve::float32(eve::exp2)(pi) << '\n'
            << "-> float64(exp2)(pi)   = " << eve::float64(eve::exp2)(pi) << '\n'
            << "-> floating_(exp2)(pi) = " << eve::floating_(eve::exp2)(pi) << '\n'
            << "-> float32(exp2(pi))   = " << eve::float32(eve::exp2(pi)) << '\n'
            << "-> float64(exp2(pi))   = " << eve::float64(eve::exp2(pi)) << '\n'
            << "-> floating_(exp2(pi)) = " << eve::floating_(eve::exp2(pi)) << '\n';

  float xf = 1.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf       = " << xf << '\n'
            << "-> exp2(xf) = " << eve::exp2(xf) << '\n';
  return 0;
}
