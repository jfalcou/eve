#include <eve/function/zeta.hpp>
#include <eve/wide.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{
  using eve::pedantic;

wide_ft pf = {0.0f, -1.0f, 1.0f, -1.5f, 1.5f, -2.0f, 2.0f, -12.0f};

  std::cout << "---- simd" << '\n'
            << "<- pf       = " << pf << '\n'
            << "-> zeta(pf) = " << eve::zeta(pf) << '\n';

  float xf = 2.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf       = " << xf << '\n'
            << "-> zeta(xf) = " << eve::zeta(xf) << '\n';
  return 0;
}
