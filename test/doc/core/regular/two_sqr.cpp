#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  float ep = eve::eps(eve::as<float>());
  wide_ft pf = {1.0f, 0.5f*(1.0f+ep*4), -1.3f,   1.0f+ep};

  auto [a, e]  = eve::two_sqr(pf);
  std::cout << "---- simd" << std::setprecision(10) << '\n'
            << "<- pf               = " << pf << '\n'
            << "-> two_sqr(pf)  = [" << '\n'
            << "                   " << a << ", \n"
            << "                   " << e << '\n'
            << "                  ]\n";
  auto [b, f]  = eve::two_prod(pf, pf);
  std::cout << "---- simd" << std::setprecision(10) << '\n'
            << "<- pf               = " << pf << '\n'
            << "-> two_prod(pf, pf)  = [" << '\n'
            << "                   " << b << ", \n"
            << "                   " << f << '\n'
            << "                  ]\n";

  float xf = 120.3;
  auto [sa, se] =  eve::two_sqr(xf);

  std::cout << "---- scalar" << '\n'
            << "<- xf          =  " << xf << '\n'
            << "-> two_sqr(xf) = [" << sa << ", " << se << "]\n";
  return 0;
}
