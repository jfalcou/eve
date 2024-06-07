#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<double, eve::fixed<8>>;

consteval auto constexpr_ifrexp(auto a) { return eve::ifrexp(a); }

int main()
{
  wide_ft pf = {-1.0f, 0.0f, 367.0f, -1005600.0f, eve::mindenormal(eve::as<double>()),
               eve::inf(eve::as<double>()), eve::minf(eve::as<double>()), eve::nan(eve::as<double>())};

  auto [m, e]    = eve::ifrexp(pf);
  auto [mp, ep]  = eve::ifrexp[eve::pedantic](pf);
  std::cout << "---- simd" << '\n'
            << "<- pf                    = " << pf << '\n'
            << "-> ifrexp(pf)            = [" << '\n'
            << "                           " << m << ", \n"
            << "                           " << e << '\n'
            << "                           ]\n"
            << "-> ifrexp[pedantic](pf)  = [" << '\n'
            << "                           " << mp << ", \n"
            << "                           " << ep << '\n'
            << "                           ]\n";

  float xf = 2.3;
  auto [sm, se] =  eve::ifrexp(xf);

  std::cout << "---- scalar" << '\n'
            << "<- xf         =  " << xf << '\n'
            << "-> ifrexp(xf) = [" << sm << ", " << se << "]\n";

//  std::cout << "-> constexpr_ifrexp(1.0f) = " << constexpr_ifrexp(1.0f) << std::endl;

  return 0;
}
