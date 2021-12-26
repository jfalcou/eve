//#include <eve/function/pedantic/ifrexp.hpp>
#include <eve/module/ieee.hpp>
#include <eve/wide.hpp>
#include <eve/constant/mindenormal.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/nan.hpp>
#include <iostream>

using wide_ft = eve::wide<double, eve::fixed<8>>;

int main()
{
  wide_ft pf = {-1.0f, 0.0f, 367.0f, -1005600.0f, eve::mindenormal(eve::as<double>()),
               eve::inf(eve::as<double>()), eve::minf(eve::as<double>()), eve::nan(eve::as<double>())};

  auto [m, e]    = eve::ifrexp(pf);
  auto [mp, ep]  = eve::pedantic(eve::ifrexp)(pf);
  std::cout << "---- simd" << '\n'
            << "<- pf                    = " << pf << '\n'
            << "-> ifrexp(pf)            = [" << '\n'
            << "                           " << m << ", \n"
            << "                           " << e << '\n'
            << "                           ]\n"
            << "-> pedantic(ifrexp)(pf) = [" << '\n'
            << "                           " << mp << ", \n"
            << "                           " << ep << '\n'
            << "                           ]\n";

  float xf = 2.3;
  auto [sm, se] =  eve::ifrexp(xf);

  std::cout << "---- scalar" << '\n'
            << "<- xf         =  " << xf << '\n'
            << "-> ifrexp(xf) = [" << sm << ", " << se << "]\n";
  return 0;
}
