//#include <eve/function/pedantic/frexp.hpp>
#include <eve/module/arithmetic.hpp>
#include <eve/wide.hpp>
#include <eve/module/arithmetic/constant/mindenormal.hpp>
#include <eve/module/core/constant/minf.hpp>
#include <eve/module/core/constant/inf.hpp>
#include <eve/module/core/constant/nan.hpp>
#include <iostream>

using wide_ft = eve::wide<double, eve::fixed<8>>;

int main()
{
  wide_ft pf = {-1.0f, 0.0f, 367.0f, -1005600.0f, eve::mindenormal(eve::as<double>()),
               eve::inf(eve::as<double>()), eve::minf(eve::as<double>()), eve::nan(eve::as<double>())};

  auto [m, e]    = eve::frexp(pf);
  auto [mp, ep]  = eve::pedantic(eve::frexp)(pf);
  std::cout << "---- simd" << '\n'
            << "<- pf                   = " << pf << '\n'
            << "-> frexp(pf)            = [" << '\n'
            << "                          " << m << ", \n"
            << "                          " << e << '\n'
            << "                          ]\n"
            << "-> pedantic(frexp)(pf) = [" << '\n'
            << "                          " << mp << ", \n"
            << "                          " << ep << '\n'
            << "                          ]\n";

  float xf = 2.3;
  auto [sm, se] =  eve::frexp(xf);

  std::cout << "---- scalar" << '\n'
            << "<- xf        =  " << xf << '\n'
            << "-> frexp(xf) = [" << sm << ", " << se << "]\n";
  return 0;
}
