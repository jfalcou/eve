#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{

  wide_ft pf = {0.0f, -0.0f, -1.0f, 1.0f, 2.0f,
               eve::inf(eve::as<float>()), eve::minf(eve::as<float>()), eve::nan(eve::as<float>())};

  std::cout << "---- simd" << '\n'
            << "<- pf        = " << pf << '\n'
            << "-> exp10(pf) = " << eve::exp10(pf) << '\n'
            << "-> diff(exp10)(pf) = " << eve::diff(eve::exp10)(pf) << '\n';

  float xf = 1.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf        = " << xf << '\n'
            << "-> exp10(xf) = " << eve::exp10(xf) << '\n';
  return 0;
}
