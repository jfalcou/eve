#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{
  wide_ft pf = {-0.0,  1.30f, -1.3f,  eve::inf(eve::as<float>()),  0.0f,
                eve::nan(eve::as<float>()), 2.0f,  eve::prev(2.0f)};

  auto [m, e]    = eve::modf(pf);
  auto [mp, ep]  = eve::modf[eve::pedantic](pf);
  auto [mr, er]  = eve::modf[eve::raw](pf);
  auto [ma, ea]  = eve::modf[eve::almost = 4](pf);
  std::cout << "---- simd" << std::setprecision(8) << '\n'
            << "<- pf                  = " << pf << '\n'
            << "-> modf(pf)            = [" << '\n'
            << "                          " << m << ", \n"
            << "                          " << e << '\n'
            << "                         ]\n"
            << "-> modf[pedantic](pf)  = [" << '\n'
            << "                          " << mp << ", \n"
            << "                          " << ep << '\n'
            << "                         ]\n"
            << "-> modf[raw](pf)       = [" << '\n'
            << "                          " << mr << ", \n"
            << "                          " << er << '\n'
            << "                         ]\n"
            << "-> modf[almost = 4](pf)    = [" << '\n'
            << "                          " << ma << ", \n"
            << "                          " << ea << '\n'
            << "                         ]\n"

    ;

  float xf = 2.3;
  auto [sm, se] =  eve::modf(xf);

  std::cout << "---- scalar" << '\n'
            << "<- xf       =  " << xf << '\n'
            << "-> modf(xf) = [" << sm << ", " << se << "]\n";
  return 0;
}
