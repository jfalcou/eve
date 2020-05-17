#include <eve/function/cot.hpp>
#include <eve/wide.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/pi.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft pf = {1.0f, 0.0f, eve::Inf<float>(), eve::Pi<float>()};

  std::cout << "---- simd" << '\n'
            << "<- pf       = " << pf << '\n'
            << "-> cot(pf) = " << eve::cot(pf) << '\n';

  float xf = 3.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf       = " << xf << '\n'
            << "-> cot(xf) = " << eve::cot(xf) << '\n';
  return 0;
}
