//#include <eve/function/sincos.hpp>
#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <eve/module/math/constant/pi.hpp>
#include <eve/module/core/constant/inf.hpp>
#include <iostream>

using wide_ft = eve::wide<double, eve::fixed<4>>;

int main()
{
  wide_ft pf = {1.0f, 0.0f, eve::inf(eve::as<float>()), eve::pi(eve::as<float>())};

  auto [s, c]    = eve::sincos(pf);
  std::cout << "---- simd" << '\n'
            << "<- pf          = " << pf << '\n'
            << "-> sincos(pf)  = [" << '\n'
            << "                  " << s << ", \n"
            << "                  " << c << '\n'
            << "                 ]\n";

  float xf = 2.3;
  auto [ss, sc] =  eve::sincos(xf);

  std::cout << "---- scalar" << '\n'
            << "<- xf         =  " << xf << '\n'
            << "-> sincos(xf) = [" << ss << ", " << sc << "]\n";
  return 0;
}
