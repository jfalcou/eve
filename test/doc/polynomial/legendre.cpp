// revision 1
#include <eve/module/polynomial.hpp>
#include <iostream>

int main()
{

  eve::wide n = {0, 1, 2, 3, 4, 5, 6, 7};
  eve::wide xd = {-0.1, -0.2, -0.3, -0.5, 0.0, 0.2, 0.3, 2.0};
  double    x(0.5);
  double    z(1);

  std::cout << "<- xd                                = " << xd << '\n';
  std::cout << "<- n                                 = " << n  << '\n';
  std::cout << "<- x                                 = " << x  << '\n';
  std::cout << "<- z                                 = " << z  << '\n';

  // std::cout << "-> legendre(n, xd)                   = " << eve::legendre(n, xd) << '\n';
  // std::cout << "-> legendre[ignore_last(2)](n, xd)   = " << eve::legendre[eve::ignore_last(2)](n, xd) << "\n";
  // std::cout << "-> legendre[n > 3](n, xd)            = " << eve::legendre[n > 3](n, xd) << "\n";
  // std::cout << "-> legendre(3, xd)                   = " << eve::legendre(3, xd) << '\n';
  // std::cout << "-> legendre(n, 0.5)                  = " << eve::legendre(n, 0.5) << '\n';
  // std::cout << "-> legendre(n, x)                    = " << eve::legendre(n, x)   << '\n';
  // std::cout << "-> legendre[p_kind](n, xd)           = " << eve::legendre[eve::p_kind](n, xd) << '\n';
  // std::cout << "-> legendre[q_kind](n, xd)           = " << eve::legendre[eve::q_kind](n, xd) << '\n';
  // std::cout << "-> legendre[spherical](n, z, xd)     = " << eve::legendre[eve::spherical](n, z, xd) << '\n';
  std::cout << "-> legendre[associated(n, z, xd)     = " << eve::legendre[eve::associated](n, z, xd) << '\n';
  // std::cout << "-> legendre[condon_shortley(n, z, xd = " << eve::legendre[eve::condon_shortley](n, z, xd) << '\n';
}
