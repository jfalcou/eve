// revision 1 TODO
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

  std::cout << "<- xd                               = " << xd << '\n';
  std::cout << "<- x                                = " << x  << '\n';
  std::cout << "<- v                                = " << v  << '\n';
  std::cout << "<- wv                               = " << wv << '\n';
  std::cout << "-> horner(xd, 1.0, -2.0, 3.0, -4.0) = " << eve::horner(xd, 1.0, -2.0, 3.0, -4.0) << '\n';
  std::cout << "-> horner(0.5, 1, b, 3, -4)         = " << eve::horner(0.5, 1, b, 3, -4) << '\n';
  std::cout << "-> horner(x, 1, -2, 3, -4)          = " << eve::horner(xd, 1, -2, 3, -4)  << '\n';
  std::cout << "-> horner(xd, v)                    = " << eve::horner(xd, v)  << '\n';
  std::cout << "-> horner(xd, t)                    = " << eve::horner(xd, t)   << '\n';
  std::cout << "-> horner(x, t)                     = " << eve::horner(x, t)   << '\n';
  std::cout << "-> horner(x, wv)                    = " << eve::horner(x, wv) << '\n';
  std::cout << "-> horner(0.5f, wv)                 = " << eve::horner(0.5, wv) << '\n';
  std::cout << "-> horner(xd, wv)                   = " << eve::horner(xd, wv) << '\n';
  std::cout << "-> horner(1.0, t)                   = " << eve::horner(1.0, t) << '\n';
}
