#include <eve/function/acosh.hpp>
#include <eve/wide.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/nan.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft pf = {1.0f, 2.0f, eve::Inf<float>(), eve::Nan<float>()};

  std::cout << "---- simd" << '\n'
            << "<- pf        = " << pf << '\n'
            << "-> acosh(pf) = " << eve::acosh(pf) << '\n';

  float xf = 1.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf        = " << xf << '\n'
            << "-> acosh(xf) = " << eve::acosh(xf) << '\n';
  return 0;
}
