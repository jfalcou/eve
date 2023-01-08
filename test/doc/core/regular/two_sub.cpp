#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  float ep = eve::eps(eve::as<float>());
  wide_ft pf = {1.0f, 0.5f*(1.0f+ep*4), -1.3f,   1.0f+ep};
  wide_ft qf = {ep/8, 0.5f,             -1.3f,   -ep/2};


  auto [a, e]  = eve::two_sub(pf, qf);
  std::cout << "---- simd" << std::setprecision(10) << '\n'
            << "<- pf               = " << pf << '\n'
            << "<- qf               = " << qf << '\n'
            << "-> two_sub(pf, qf)  = [" << '\n'
            << "                      " << a << ", \n"
            << "                      " << e << '\n'
            << "                      ]\n";

  float xf = 120.3, yf = 130*ep;
  auto [sa, se] =  eve::two_sub(xf, yf);

  std::cout << "---- scalar" << '\n'
            << "<- xf              =  " << xf << '\n'
            << "<- yf              =  " << yf << '\n'
            << "-> two_sub(xf, yf) = [" << sa << ", " << se << "]\n";
  return 0;
}
