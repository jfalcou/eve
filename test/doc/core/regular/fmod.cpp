#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_it = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_it pf = {0, 1, -1, -eve::valmax(eve::as<float>())};
  wide_it qf = {1, -1, 0, eve::valmax(eve::as<float>())};

  std::cout << "---- simd" << '\n'
            << "<- pf                     = " << pf << '\n'
            << "<- qf                     = " << qf << '\n'
            << "-> fmod(pf, qf)           = " << eve::fmod(pf, qf) << '\n'


            << '\n';

  float xf = -eve::valmax(eve::as<float>());
  float yf = eve::valmax(eve::as<float>());

  std::cout << "---- scalar" << '\n'
            << "<- xf           = " << xf << '\n'
            << "<- yf           = " << yf << '\n'
            << "-> fmod(xf, yf) = " << eve::fmod(xf, yf) << '\n'
            << '\n';
  return 0;
}
