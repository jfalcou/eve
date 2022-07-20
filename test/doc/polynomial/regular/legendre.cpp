#include <eve/module/polynomial.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<double, eve::fixed<8>>;
using wide_it = eve::wide<int   , eve::fixed<8>>;

int main()
{

  wide_ft xd = {-0.1, -0.2, -0.3, -0.5, 0.0, 0.2, 0.3, 2.0};
  wide_it n = {0, 1, 2, 3, 4, 5, 6, 7};
  wide_ft x(0.5);

  std::cout << "---- simd" << '\n'
            << "<- xd               = " << xd << '\n'
            << "<- n                = " << n  << '\n'
            << "<- x                = " << x  << '\n'
            << "-> legendre(n, xd)   = " << eve::legendre(n, xd) << '\n'
            << "-> legendre(3, xd)   = " << eve::legendre(3, xd) << '\n'
            << "-> legendre(n, 0.5)  = " << eve::legendre(n, 0.5) << '\n'
            << "-> legendre(n, x)    = " << eve::legendre(n, x)   << '\n'
            ;

  double xs = 0.1;

  std::cout << "---- scalar" << '\n'
            << "<- xs               = " << xs << '\n'
            << "-> legendre(4, xs)   = " << eve::legendre(4, xs) << '\n';

  return 0;
}
