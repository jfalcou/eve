#include <eve/function/ulpdist.hpp>
#include <eve/wide.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/tags.hpp>
#include <iostream>

using wide_it = eve::wide<int16_t, eve::fixed<4>>;

int main()
{
  wide_it pf = {0, 1, -1, -eve::Valmax<int16_t>()};
  wide_it qf = {1, -1, 0, eve::Valmax<int16_t>()};

  std::cout << "---- simd" << '\n'
            << "<- pf =                          " << pf << '\n'
            << "<- qf =                          " << qf << '\n'
            << "-> eve::ulpdist(pf, qf) =            " << eve::ulpdist(pf, qf) << '\n'
            << '\n';

  int16_t xf = -eve::Valmax<int16_t>();
  int16_t yf = eve::Valmax<int16_t>();

  std::cout << "---- scalar" << '\n'
            << "<- xf =                          " << xf << '\n'
            << "<- yf =                          " << yf << '\n'
            << "-> eve::ulpdist(xf, yf) =            " << eve::ulpdist(xf, yf) << '\n'
            << '\n';
  return 0;
}
