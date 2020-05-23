#include <eve/function/fdim.hpp>
#include <eve/wide.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <iostream>

using wide_it = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_it pf = {0, 1, -1, -eve::Valmax<float>()};
  wide_it qf = {1, -1, 0, eve::Valmax<float>()};

  std::cout << "---- simd" << '\n'
            << "<- pf           = " << pf << '\n'
            << "<- qf           = " << qf << '\n'
            << "-> fdim(pf, qf) = " << eve::fdim(pf, qf) << '\n'
            << '\n';

  float xf = -eve::Valmax<float>();
  float yf = eve::Valmax<float>();

  std::cout << "---- scalar" << '\n'
            << "<- xf           = " << xf << '\n'
            << "<- yf           = " << yf << '\n'
            << "-> fdim(xf, yf) = " << eve::fdim(xf, yf) << '\n'
            << '\n';
  return 0;
}
