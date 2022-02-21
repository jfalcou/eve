#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <eve/module/core/constant/mindenormal.hpp>
#include <eve/module/core/constant/minf.hpp>
#include <eve/module/core/constant/inf.hpp>
#include <eve/module/core/constant/nan.hpp>
#include <iostream>

using wide_ft = eve::wide<double, eve::fixed<8>>;

int main()
{
  wide_ft pf = {-1.0f, 0.0f, 367.0f, -1005600.0f, eve::mindenormal(eve::as<double>()),
               eve::inf(eve::as<double>()), eve::minf(eve::as<double>()), eve::nan(eve::as<double>())};

  auto [s, c]    = eve::sinhcosh(pf);
  std::cout << "---- simd" << '\n'
            << "<- pf                      = " << pf << '\n'
            << "-> sinhcosh(pf)            = [" << '\n'
            << "                              " << s << ", \n"
            << "                              " << c << '\n'
            << "                             ]\n";

  float xf = 2.3;
  auto [ss, sc] =  eve::sinhcosh(xf);

  std::cout << "---- scalar" << '\n'
            << "<- xf           =  " << xf << '\n'
            << "-> sinhcosh(xf) = [" << ss << ", " << sc << "]\n";
  return 0;
}
