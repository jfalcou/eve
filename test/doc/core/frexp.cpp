#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<double, eve::fixed<8>>;

consteval auto constexpr_frexp(auto a) { return eve::frexp(a); }

int main()
{
  wide_ft pf = {-1.0f, 0.0f, 367.0f, -1005600.0f, eve::mindenormal(eve::as<double>()),
               eve::inf(eve::as<double>()), eve::minf(eve::as<double>()), eve::nan(eve::as<double>())};

  auto [m, e]    = eve::frexp(pf);
  auto [mp, ep]  = eve::frexp[eve::pedantic](pf);
  std::cout << "---- simd" << '\n'
            << "<- pf                   = " << pf << '\n'
            << "-> frexp(pf)            = [" << '\n'
            << "                          " << m << ", \n"
            << "                          " << e << '\n'
            << "                          ]\n"
            << "-> frexp[pedantic](pf)  = [" << '\n'
            << "                          " << mp << ", \n"
            << "                          " << ep << '\n'
            << "                          ]\n";

  float xf = 2.3;
  auto [sm, se] =  eve::frexp(xf);

  std::cout << "---- scalar" << '\n'
            << "<- xf        =  " << xf << '\n'
            << "-> frexp(xf) = [" << sm << ", " << se << "]\n";

//  std::cout << "-> constexpr_frexp(1.0f) = " << constexpr_frexp(1.0f) << std::endl;

  return 0;
}
