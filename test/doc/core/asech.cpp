#include <eve/function/asech.hpp>
#include <eve/wide.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/nan.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft pf = {1.0f, 0.5f, eve::Inf<float>(), eve::Nan<float>()};

  std::cout << "---- simd" << '\n'
            << "<- pf        = " << pf << '\n'
            << "-> asech(pf) = " << eve::asech(pf) << '\n';

  float xf = 1.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf        = " << xf << '\n'
            << "-> asech(xf) = " << eve::asech(xf) << '\n';
  return 0;
}
