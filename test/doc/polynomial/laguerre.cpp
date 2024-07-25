// revision 1
#include <eve/module/polynomial.hpp>
#include <iostream>

int main()
{
  eve::wide n{0, 1, 2, 3, 4, 5, 6, 7};
  eve::wide m{0, 1, 2, 3, 4, 5, 6, 7};
  eve::wide xd{0.5, -1.5, 0.1, -1.0, 19.0, 25.0, 21.5, 10000.0};
  double    x(0.5);

  std::cout << "<- n                                = " << n  << '\n';
  std::cout << "<- m                                = " << m  << '\n';
  std::cout << "<- xd                               = " << xd << '\n';
  std::cout << "<- x                                = " << x  << '\n';

  std::cout << "-> laguerre(n, xd)                  = " << eve::laguerre(n, xd)  << '\n';
  std::cout << "-> laguerre[ignore_last(2)](n, xd)  = " << eve::laguerre[eve::ignore_last(2)](n, xd)  << '\n';
  std::cout << "-> laguerre[n > 3](n, xd)           = " << eve::laguerre[n > 3](n, xd)  << '\n';
  std::cout << "-> laguerre(3, xd)                  = " << eve::laguerre(3, xd)  << '\n';
  std::cout << "-> laguerre(n, x)                   = " << eve::laguerre(n, x)   << '\n';

  std::cout << "-> laguerre[associated](n, m, xd)   = " << eve::laguerre[eve::associated](n, m, xd) << '\n';
  std::cout << "-> laguerre[associated](3, m, xd)   = " << eve::laguerre[eve::associated](3, m, xd) << '\n';
  std::cout << "-> laguerre[associated](n, 3, xd)   = " << eve::laguerre[eve::associated](n, 3, xd) << '\n';
  std::cout << "-> laguerre[associated](n, m, x)    = " << eve::laguerre[eve::associated](n, m, x) << '\n';

}
