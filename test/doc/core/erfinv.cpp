#include <eve/function/erfinv.hpp>
#include <eve/wide.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{
  using eve::pedantic;

  wide_ft pf = {0.5f, -0.5f, -1.0f, 1.0f, -0.0f, 0.0f, 0.75f,
                eve::nan(eve::as<float>())};
  auto r = eve::erfinv(pf);

  std::cout << "---- simd" << '\n'
            << "<- pf        = " << pf << '\n'
            << "-> erfinv(pf) = " << r << '\n';

  float xf = -1.0f;
  float rf = eve::erfinv(xf);
  std::cout << "---- scalar" << '\n'
            << "<- xf        = " << xf << '\n'
            << "-> erfinv(xf) = " << rf << '\n';
  return 0;
}
