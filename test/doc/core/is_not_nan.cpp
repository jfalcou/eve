#include <eve/function/is_not_nan.hpp>
#include <eve/wide.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{
  wide_ft pf = {0.0f, 1.0f, -1.5f, -2.0f, eve::Nan<float>(),
                eve::Inf<float>(), eve::Minf<float>(), -eve::Nan<float>()};

  std::cout << "---- simd" << '\n'
            << "<- pf             = " << pf << '\n'
            << "-> is_not_nan(pf) = " << eve::is_not_nan(pf) << '\n';

  float xf = 1.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf             = " << xf << '\n'
            << "-> is_not_nan(xf) = " << eve::is_not_nan(xf) << '\n';
  return 0;
}
