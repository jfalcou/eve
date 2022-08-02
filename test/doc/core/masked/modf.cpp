#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{
  wide_ft pf = {-0.0,  1.30f, -1.3f,  eve::inf(eve::as<float>()),  0.0f,
                eve::nan(eve::as<float>()), 0.678f,   -0.678f};

  auto [m, e]    = eve::modf(pf);
  auto [mp, ep]  = eve::pedantic(eve::modf)(pf);
  std::cout << "---- simd" << '\n'
            << "<- pf                  = " << pf << '\n'
            << "-> modf(pf)            = [" << '\n'
            << "                          " << m << ", \n"
            << "                          " << e << '\n'
            << "                         ]\n"
            << "-> pedantic(modf)(pf) = [" << '\n'
            << "                          " << mp << ", \n"
            << "                          " << ep << '\n'
            << "                         ]\n";

  float xf = 2.3;
  auto [sm, se] =  eve::modf(xf);

  std::cout << "---- scalar" << '\n'
            << "<- xf       =  " << xf << '\n'
            << "-> modf(xf) = [" << sm << ", " << se << "]\n";
  return 0;
}
