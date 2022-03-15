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
            << "-> fdim(pf, qf)           = " << eve::fdim(pf, qf) << '\n'
            << "-> diff_1st(fdim)(pf, qf) = " << eve::diff_1st(eve::fdim)(pf, qf) << '\n'
            << "-> diff_2nd(fdim)(pf, qf) = " << eve::diff_2nd(eve::fdim)(pf, qf) << '\n'
            << '\n';

  float xf = -eve::valmax(eve::as<float>());
  float yf = eve::valmax(eve::as<float>());

  std::cout << "---- scalar" << '\n'
            << "<- xf           = " << xf << '\n'
            << "<- yf           = " << yf << '\n'
            << "-> fdim(xf, yf) = " << eve::fdim(xf, yf) << '\n'
            << '\n';
  return 0;
}
