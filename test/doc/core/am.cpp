#include <eve/function/am.hpp>
#include <eve/wide.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/pi.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft pf = {1.0f, 0.0f, eve::inf(eve::as<float>()), eve::pi(eve::as<float>())};
  wide_ft qf = {1.0f, 0.0f, 0.1f, 0.5f};

  std::cout << "---- simd" << '\n'
            << "<- pf      = " << pf << '\n'
            << "<- qf      = " << qf << '\n'
            << "-> am(pf, qf) = " << eve::am(pf, qf) << '\n';

  float xf = 3.0f;
  float yf = 0.5f;

  std::cout << "---- scalar" << '\n'
            << "<- xf      = " << xf << '\n'
            << "<- yf      = " << yf << '\n'
            << "-> am(xf, yf) = " << eve::am(xf, yf) << '\n';
  return 0;
}
