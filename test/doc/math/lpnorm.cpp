#include <eve/module/math.hpp>
#include <eve/function/pedantic/lpnorm.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft x = {eve::nan(eve::as<float>()), 1.0f, 1.0f, 1.0f};
  wide_ft y = {-1.5f, 2.9f, 3.5f, -11.0f};
  wide_ft z = { eve::inf(eve::as(1.0f)), -2.0f, 1.0f, eve::nan(eve::as<float>())};
  wide_ft p = { 3.2f, 3.0f, 2.0f, eve::inf(eve::as(1.0f))};

    std::cout << "---- simd" << std::setprecision(5) << '\n'
              << "<- p                            = " << p  << '\n'
              << "<- x                            = " << x  << '\n'
              << "<- y                            = " << y  << '\n'
              << "<- z                            = " << z  << '\n'
              << "-> lpnorm(p, x, y, z)           = " << eve::lpnorm(p, x, y, z) << '\n'
              << "-> pedantic(lpnorm)(p, x, y, z) = " << eve::pedantic(eve::lpnorm)(p, x, y, z) << '\n';


  double        xf = 10.0;
  double        yf = 1.0;
  double        zf = 111.0;
  double        pf = 2.0; //eve::inf(eve::as(xf));

  std::cout << "---- scalar" << '\n'
            << "<- pf                               = " << pf << '\n'
            << "<- xf                               = " << xf << '\n'
            << "<- yf                               = " << yf << '\n'
            << "<- zf                               = " << zf << '\n'
            << "-> lpnorm(p, xf, yf, zf)            = " << eve::lpnorm(pf, xf, yf, zf) << '\n'
            << "-> pedantic(lpnorm)(p, xf, yf, zf)  = " << eve::pedantic(eve::lpnorm)(pf, xf, yf, zf) << '\n';
  return 0;
}
