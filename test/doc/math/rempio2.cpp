//#include <eve/function/rempio2.hpp>
#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <eve/constant/pi.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{
  wide_ft pf = {-1.0f, 0.0f, 367.0f, -1005600.0f, eve::pi(eve::as<float>())/8,
               eve::pi(eve::as<float>())/3, -eve::pi(eve::as<float>())/3, 2*eve::pi(eve::as<float>())/3};

  auto [n, x, dx]    = eve::rempio2(pf);
  std::cout << "---- simd" << '\n'
            << "<- pf          = " << pf << '\n'
            << "-> rempio2(pf) = [" << '\n'
            << "               " << n << ", \n"
            << "               " << x << '\n'
            << "               " << dx << '\n'
            << "                ]\n";

  float xf = 2.3;
  auto [sn, sx, sdx] =  eve::rempio2(xf);

  std::cout << "---- scalar" << '\n'
            << "<- xf       =  " << xf << '\n'
            << "-> rempio2(xf) = [" << sn << ", " << sx << ", " << sdx << "]\n";
  return 0;
}
