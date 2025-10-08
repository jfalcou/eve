// revision 1
#include <eve/module/math.hpp>
#include <iostream>
#include <iomanip>

int main()
{
  eve::wide xd = {-0.3, 0.5, 0.0, 2.0};
  eve::wide b  = {-2.0, 10.5, -4.0, 0.1};
  double x(0.2);
  kumi::tuple v {1.0, -2.0, 3.0, -4.0};
  using w_t = decltype(xd);
  kumi::tuple wv{ w_t{1.5, 1, 2, 3}, w_t{4, 5, 6, 7}, w_t{8, 9, 10, 11} };
  auto t = kumi::tuple{1.5,4.0,8.0};

  std::cout << "<- xd                                       = " << xd << '\n';
  std::cout << "<- x                                        = " << x  << '\n';
  std::cout << "<- v                                        = " << v  << '\n';
  std::cout << "<- wv                                       = " << wv << '\n';
  std::cout << "-> reverse_horner(xd, 1.0, -2.0, 3.0, -4.0) = " << eve::reverse_horner(xd, 1.0, -2.0, 3.0, -4.0) << '\n';
  std::cout << "-> reverse_horner(0.5, 1, b, 3, -4)         = " << eve::reverse_horner(0.5, 1, b, 3, -4) << '\n';
  std::cout << "-> reverse_horner(x, 1, -2, 3, -4)          = " << eve::reverse_horner(xd, 1, -2, 3, -4)  << '\n';
  std::cout << "-> reverse_horner(xd, v)                    = " << eve::reverse_horner(xd, eve::coefficients(v))  << '\n';
  std::cout << "-> reverse_horner(xd, t)                    = " << eve::reverse_horner(xd, eve::coefficients(t))   << '\n';
  std::cout << "-> reverse_horner(x, t)                     = " << eve::reverse_horner(x, eve::coefficients(t))   << '\n';
  std::cout << "-> reverse_horner(x, wv)                    = " << eve::reverse_horner(x, eve::coefficients(wv)) << '\n';
  std::cout << "-> reverse_horner(0.5f, wv)                 = " << eve::reverse_horner(0.5, eve::coefficients(wv)) << '\n';
  std::cout << "-> reverse_horner(xd, wv)                   = " << eve::reverse_horner(xd, eve::coefficients(wv)) << '\n';
  std::cout << "-> reverse_horner(2.0, t)                   = " << eve::reverse_horner(2.0, eve::coefficients(t)) << '\n';
  std::cout << "-> reverse_horner(2.0, 1.5,4.0,8.0)         = " << eve::reverse_horner(2.0, 1.5,4.0,8.0) << '\n';
  std::cout << "-> reverse_horner                           = " << eve::reverse_horner(w_t(2.0),  1.5,4.0,8.0) << '\n';
}
