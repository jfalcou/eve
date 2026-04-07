#include <eve/module/math.hpp>
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
              << "-> lpnorm[pedantic](p, x, y, z) = " << eve::lpnorm[eve::pedantic](p, x, y, z) << '\n'


              ;

  double        xf = 10.0;
  double        yf = 1.0;
  double        zf = 111.0;
  double        pf = 2.0;

  std::cout << "---- scalar" << '\n'
            << "<- pf                               = " << pf << '\n'
            << "<- xf                               = " << xf << '\n'
            << "<- yf                               = " << yf << '\n'
            << "<- zf                               = " << zf << '\n'
            << "-> lpnorm(pf, xf, yf, zf)           = " << eve::lpnorm(pf, xf, yf, zf) << '\n'
            << "-> lpnorm[pedantic](pf, xf, yf, zf) = " << eve::lpnorm[eve::pedantic](pf, xf, yf, zf) << '\n';

  float o = 1.0f;
  float i = eve::inf(eve::as(o));
  float n = eve::nan(eve::as(o));
  float ma= eve::valmax(eve::as(o));
  float m = (ma/3)*2;
  std::cout << "<- o                                = " << o << "\n";
  std::cout << "-> i                                = " << i << "\n";
  std::cout << "-> n                                = " << n << "\n";
  std::cout << "-> lpnorm(3, i, o, -i)                 = " << eve::lpnorm(3, i, o, -i) << "\n";
  std::cout << "-> lpnorm(3, i, o, n)                  = " << eve::lpnorm(3, i, o, n) << "\n";
  std::cout << "-> lpnorm[pedantic](3, o, o, n)        = " << eve::lpnorm[eve::pedantic](3, o, o, n) << "\n";
  std::cout << "-> lpnorm[pedantic](3, o, n, o)        = " << eve::lpnorm[eve::pedantic](3, o, n, o) << "\n";
  std::cout << "-> lpnorm[pedantic](3, n, o, o)        = " << eve::lpnorm[eve::pedantic](3, n, o, o) << "\n";
  std::cout << "-> lpnorm[pedantic](3, n, m, m)        = " << eve::lpnorm[eve::pedantic](3, n, m, m) << "\n";
  std::cout << "-> lpnorm          (3, o, o, n)        = " << eve::lpnorm(3, o, o, n) << "\n";
  std::cout << "-> lpnorm          (3, o, n, o)        = " << eve::lpnorm(3, o, n, o) << "\n";
  std::cout << "-> lpnorm          (3, n, o, o)        = " << eve::lpnorm(3, n, o, o) << "\n";
  std::cout << "-> lpnorm          (3, n, m, m)        = " << eve::lpnorm(3, n, m, m) << "\n";
  std::cout << "-> lpnorm(3, n, n, n)                  = " << eve::lpnorm(3, n, n, n) << "\n";
  std::cout << "-> lpnorm(3, m, o, o)                  = " << eve::lpnorm(3, m, o, o)<< "\n";
  std::cout << "-> lpnorm[pedantic](3, m, o, o)        = " << eve::lpnorm[eve::pedantic](3, m, o, o)<< "\n";
  std::cout << "-> lpnorm[pedantic](3, i, o, n)        = " << eve::lpnorm[eve::pedantic](3, i, o, n) << "\n";
  std::cout << "-> lpnorm[pedantic](3, m)              = " << eve::lpnorm[eve::pedantic](3, m) << "\n";
  std::cout << "-> lpnorm[pedantic](3, m, m)           = " << eve::lpnorm[eve::pedantic](3, m, m) << "\n";
  std::cout << "-> lpnorm[pedantic](3, m, m, m)        = " << eve::lpnorm[eve::pedantic](3, m, m, m) << "\n";
  std::cout << "-> lpnorm[pedantic](3, m, m, m, m)     = " << eve::lpnorm[eve::pedantic](3, m, m, m, m) << "\n";
  std::cout << "-> lpnorm[pedantic](3, m, o, o)        = " << eve::lpnorm[eve::pedantic](3, m, o, o)<< "\n";
  std::cout << "-> lpnorm(3, i, o, n)                  = " << eve::lpnorm(3, i, o, n) << "\n";
  std::cout << "-> lpnorm(3, m)                        = " << eve::lpnorm(3, m) << "\n";
  std::cout << "-> lpnorm(3, m, m)                     = " << eve::lpnorm(3, m, m) << "\n";
  std::cout << "-> lpnorm(3, m, m, m)                  = " << eve::lpnorm(3, m, m, m) << "\n";
  std::cout << "-> lpnorm(3, m, m, m, m)               = " << eve::lpnorm(3, m, m, m, m) << "\n";

  std::cout << "-> lpnorm[pedantic](3, m, n)              = " << eve::lpnorm[eve::pedantic](3, m, n) << "\n";
  std::cout << "-> lpnorm[pedantic](3, m, m, n)           = " << eve::lpnorm[eve::pedantic](3, m, m, n) << "\n";
  std::cout << "-> lpnorm[pedantic](3, m, m, m, n)        = " << eve::lpnorm[eve::pedantic](3, m, m, m, n) << "\n";
  std::cout << "-> lpnorm[pedantic](3, m, m, m, m, n)     = " << eve::lpnorm[eve::pedantic](3, m, m, m, m, n) << "\n";

  std::cout << "-> lpnorm(i, m)                        = " << eve::lpnorm(i, m) << "\n";
  std::cout << "-> lpnorm(i, m, m)                     = " << eve::lpnorm(i, m, m) << "\n";
  std::cout << "-> lpnorm(i, m, m, m)                  = " << eve::lpnorm(i, m, m, m) << "\n";
  std::cout << "-> lpnorm(i, m, m, m, m)               = " << eve::lpnorm(i, m, m, m, m) << "\n";

  std::cout << "-> lpnorm[pedantic](i, m, n)              = " << eve::lpnorm[eve::pedantic](i, m, n) << "\n";
  std::cout << "-> lpnorm[pedantic](i, m, m, n)           = " << eve::lpnorm[eve::pedantic](i, m, m, n) << "\n";
  std::cout << "-> lpnorm[pedantic](i, m, m, m, n)        = " << eve::lpnorm[eve::pedantic](i, m, m, m, n) << "\n";
  std::cout << "-> lpnorm[pedantic](i, m, m, m, m, n)     = " << eve::lpnorm[eve::pedantic](i, m, m, m, m, n) << "\n";

  std::cout << "-> lpnorm[raw](3, m)                        = " << eve::lpnorm[eve::raw](3, m) << "\n";
  std::cout << "-> lpnorm[raw](3, m, m)                     = " << eve::lpnorm[eve::raw](3, m, m) << "\n";
  std::cout << "-> lpnorm[raw](3, m, m, m)                  = " << eve::lpnorm[eve::raw](3, m, m, m) << "\n";
  std::cout << "-> lpnorm[raw](3, m, m, m, m)               = " << eve::lpnorm[eve::raw](3, m, m, m, m) << "\n";
 return 0;
}
