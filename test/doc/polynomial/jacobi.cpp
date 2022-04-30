#include <eve/module/polynomial.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<double, eve::fixed<8>>;
using wide_it = eve::wide<std::int64_t   , eve::fixed<8>>;

int main()
{

  wide_ft xd = {0.5, -1.5, 0.1, -1.0, 19.0, 25.0, 21.5, 10000.0};
  wide_it n = {0, 1, 2, 3, 4, 5, 6, 7};
  wide_ft x(0.5);
  wide_ft aa{-0.75, -0.5, -0.25, 0.0, 0.25, 0.5, 0.75, 1.0};
  double a = -3/8.0;
  double b = 0.25;

  std::cout << "---- simd" << '\n'
            << "<- xd                             = " << xd << '\n'
            << "<- n                              = " << n  << '\n'
            << "<- x                              = " << x  << '\n'
            << "-> jacobi(n, a, b, xd)            = " << eve::jacobi(n, a, b, xd) << '\n'
            << "-> jacobi(4, a, b, xd)            = " << eve::jacobi(4, a, b, xd) << '\n'
            << "-> jacobi(4, a, b, x)             = " << eve::jacobi(4, a, b, x) << '\n'
            << "-> jacobi(n, a, b 0.5)            = " << eve::jacobi(n, a, b, 0.5) << '\n'
            << "-> jacobi(n, a, b, x)             = " << eve::jacobi(n, a, b, x)   << '\n'
            << "-> jacobi(n, aa, b, x)            = " << eve::jacobi(n, aa, b, x)   << '\n'
            << "-> diff(jacobi)(n, aa, b, x)      = " << eve::diff(eve::jacobi)(n, aa, b, x)   << '\n'
            << "-> diff(jacobi)(n, aa, b, x, 2)   = " << eve::diff(eve::jacobi)(n, aa, b, x, 2)   << '\n'
    ;

  double xs = 0.5;

  std::cout << "---- scalar" << '\n'
            << "<- xs               = " << xs << '\n'
            << "-> jacobi(4, xs)   = " << eve::jacobi(4, a, b, xs) << '\n';

  return 0;
}
