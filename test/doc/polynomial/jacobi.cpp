// revision 0
#include <eve/module/polynomial.hpp>
#include <iostream>

int main()
{
  eve::wide xd{0.5, -1.5, 0.1, -1.0, 19.0, 25.0, 21.5, 10000.0};
  eve::wide n{0, 1, 2, 3, 4, 5, 6, 7};
  eve::wide aa{-0.75, -0.5, -0.25, 0.0, 0.25, 0.5, 0.75, 1.0};
  double    x(0.5);
  double    a(-3/8.0);
  double    b(0.25);

  std::cout << "<- xd                                 = " << xd << '\n';
  std::cout << "<- n                                  = " << n  << '\n';
  std::cout << "<- x                                  = " << x  << '\n';
  std::cout << "<- aa                                 = " << aa << '\n';
  std::cout << "<- a                                  = " << a  << '\n';
  std::cout << "<- b                                  = " << b  << '\n';

  std::cout << "-> jacobi(n, a, b, xd)                = " << eve::jacobi(n, a, b, xd) << '\n';
  std::cout << "-> jacobi[ignore_last(2)](n, a, b, xd)= " << eve::jacobi[eve::ignore_last(2)](n, a, b, xd) << '\n';
  std::cout << "-> jacobi[n > 3](n, a, b, xd)         = " << eve::jacobi[n > 3](n, a, b, xd) << '\n';
  std::cout << "-> jacobi(4, a, b, xd)                = " << eve::jacobi(4, a, b, xd) << '\n';
  std::cout << "-> jacobi(4, a, b, x)                 = " << eve::jacobi(4, a, b, x) << '\n';
  std::cout << "-> jacobi(n, a, b 0.5)                = " << eve::jacobi(n, a, b, 0.5) << '\n';
  std::cout << "-> jacobi(n, a, b, x)                 = " << eve::jacobi(n, a, b, x)   << '\n';
  std::cout << "-> jacobi(n, aa, b, x)                = " << eve::jacobi(n, aa, b, x)   << '\n';
}
