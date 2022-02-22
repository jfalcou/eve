#include <eve/module/special.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{
  using eve::pedantic;

wide_ft pf = {0.5f, -1.5f, -1.0f, 1.0f, 2.0f,
               eve::inf(eve::as<float>()), eve::minf(eve::as<float>()), eve::nan(eve::as<float>())};

  std::cout << "---- simd" << '\n'
            << "<- pf        = " << pf << '\n'
            << "-> tgamma(pf) = " << eve::tgamma(pf) << '\n'
            << "-> diff(tgamma)(pf) = " << eve::diff(eve::tgamma)(pf) << '\n';

  float xf = 4.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf        = " << xf << '\n'
            << "-> tgamma(xf) = " << eve::tgamma(xf) << '\n';
  return 0;
}
