#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<8>>;

int main()
{
  wide_ft pf = { 0.0f, 1.0f, -1.0f, eve::pio_2(eve::as<float>())
                 ,eve::pi(eve::as<float>()), eve::inf(eve::as<float>()), eve::minf(eve::as<float>()), eve::nan(eve::as<float>()) };

  std::cout
    << "---- simd" << '\n'
    << "<- pf               = " << pf << '\n'
    << "-> radindeg(pf)     = " << eve::radindeg(pf) << '\n';

  float xf = 1.0f;
  float yf = eve::pi(eve::as<float>());

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf =                  " << xf << '\n'
    << "-> eve::radindeg(xf) =      " << eve::radindeg(xf) << '\n'
    << "<- yf =                  " << yf << '\n'
    << "-> eve::radindeg(yf) =      " << eve::radindeg(yf) << '\n';
  return 0;
}
