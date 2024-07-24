// revision 1
#include <eve/module/math.hpp>
#include <iostream>
#include <iomanip>

int main()
{
  eve::wide x = {eve::nan(eve::as<float>()), 1.0f, 1.0f, 1.0f};
  eve::wide y = {-1.5f, 2.9f, 3.5f, -11.0f};
  eve::wide z = { eve::inf(eve::as(1.0f)), -2.0f, 1.0f, 15.0f};
  eve::wide p = { 3.2f, 3.0f, 2.0f, eve::inf(eve::as(1.0f))};

  std::cout << std::setprecision(5) << '\n';
  std::cout << "<- p                            = " << p  << '\n';
  std::cout << "<- x                            = " << x  << '\n';
  std::cout << "<- y                            = " << y  << '\n';
  std::cout << "<- z                            = " << z  << '\n';
  std::cout << "-> lpnorm(p, x, y, z)           = " << eve::lpnorm(p, x, y, z) << '\n';
  std::cout << "-> lpnorm[pedantic](p, x, y, z) = " << eve::lpnorm[eve::pedantic](p, x, y, z) << '\n';
}
