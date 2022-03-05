#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iomanip>
#include <iostream>
#include <cmath>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft pf = {-1.0f, 2.0f, -3.0f, eve::valmax(eve::as<float>())/2};
  wide_ft qf = {-4, 3, -2, -12};

  std::cout << "---- simd" << std::setprecision(10) << '\n'
            << "<- pf                       = " << pf << '\n'
            << "<- qf                       = " << qf << '\n'
            << "-> hypot(pf, qf)            = " << eve::hypot(pf, qf) << '\n'
            << "-> pedantic(hypot)(pf, qf)  = " << eve::pedantic(eve::hypot)(pf, qf) << '\n';
//            << "-> diff(hypot)(pf, qf)      = " << eve::diff(eve::hypot)(pf, qf) << '\n';

  double        xf = -327680000;
  double        yf = 10;

  std::cout << "---- scalar"  << std::setprecision(15) << '\n'
            << "<- xf                       = " << xf << '\n'
            << "<- yf                       = " << yf << '\n'
            << "-> hypot(xf, yf)            = " << eve::hypot(xf, yf) << '\n'
            << "-> pedantic(hypot)(xf, yf)  = " << eve::pedantic(eve::hypot)(xf, yf) << '\n';
  return 0;
}
