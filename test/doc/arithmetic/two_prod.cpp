//#include <eve/function/two_prod.hpp>
#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <eve/module/core/constant/eps.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  float ep = eve::eps(eve::as<float>());
  wide_ft pf = {1.0f+ep, 0.5f*(1.0f+ep*4), -1.3f,   1.0f+4*ep};
  wide_ft qf = {1.0f-ep, 0.5f,             -1.3f,   1.0f-ep/2};


  auto [a, e]  = eve::two_prod(pf, qf);
  std::cout << "---- simd" << std::setprecision(10) << '\n'
            << "<- pf                = " << pf << '\n'
            << "<- qf                = " << qf << '\n'
            << "-> two_prod(pf, qf)  = [" << '\n'
            << "                      " << a << ", \n"
            << "                      " << e << '\n'
            << "                      ]\n";

  float xf = 1+ep, yf = 1-ep;
  auto [sa, se] =  eve::two_prod(xf, yf);

  std::cout << "---- scalar" << '\n'
            << "<- xf               =  " << xf << '\n'
            << "<- yf               =  " << yf << '\n'
            << "-> two_prod(xf, yf) = [" << sa << ", " << se << "]\n";
  return 0;
}
