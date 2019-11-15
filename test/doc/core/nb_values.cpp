#include <eve/function/nb_values.hpp>
#include <eve/wide.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/tags.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft pf = {0, 1, -1, -eve::Valmax<int16_t>()};
  wide_ft qf = {1, -1, 0, eve::Valmax<int16_t>()};

  std::cout << "---- simd" << '\n'
            << "<- pf =                          " << pf << '\n'
            << "<- qf =                          " << qf << '\n'
            << "-> eve::nb_values(pf, qf) =      " << eve::nb_values(pf, qf) << '\n'
            << '\n';

  int16_t xf = -eve::Valmax<int16_t>();
  int16_t yf = eve::Valmax<int16_t>();

  std::cout << "---- scalar" << '\n'
            << "<- xf =                          " << xf << '\n'
            << "<- yf =                          " << yf << '\n'
            << "-> eve::nb_values(xf, yf) =      " << eve::nb_values(xf, yf) << '\n'
            << '\n';
  return 0;
}
