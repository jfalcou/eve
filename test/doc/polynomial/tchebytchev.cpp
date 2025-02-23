// revision 1
#include <eve/module/polynomial.hpp>
#include <iostream>

int main()
{
  eve::wide xd{0.5, -1.5, 0.1, -1.0, 19.0, 25.0, 21.5, 10000.0};
  eve::wide n{0, 1, 2, 3, 4, 5, 6, 7};
  eve::wide n1{0, -1, -2, -3, -4, -5, -6, -7};
  double x(0.5);

  std::cout << "<- xd                                      = " << xd << '\n';
  std::cout << "<- n                                       = " << n  << '\n';
  std::cout << "<- x                                       = " << x  << '\n';

  std::cout << "-> tchebytchev(n, xd)                      = " << eve::tchebytchev(n, xd) << '\n';
  std::cout << "-> tchebytchev[eve::ignore_last(2)](n, xd) = " << eve::tchebytchev[eve::ignore_last(2)](n, xd) << '\n';
  std::cout << "-> tchebytchev[n > 3](n, xd)               = " << eve::tchebytchev[n >  3](n, xd) << '\n';
  std::cout << "-> tchebytchev(3, xd)                      = " << eve::tchebytchev(3, xd) << '\n';
  std::cout << "-> tchebytchev(n, 2.0)                     = " << eve::tchebytchev(n, 2.0) << '\n';
  std::cout << "-> tchebytchev(n, x)                       = " << eve::tchebytchev(n, x)   << '\n';
  std::cout << "-> tchebytchev[kind_2](n, xd)              = " << eve::tchebytchev[eve::kind_2](n, xd) << "\n\n";

  using wide_ft =  decltype(xd);
  std::array<wide_ft, 8> t;
  t[0] = eve::tchebytchev(0, xd);
  std::cout << "-> t[0]                                    = " <<  t[0] << '\n';
  std::cout << "-> tchebytchev(" << 0 << ", xd)                      = " << eve::tchebytchev(0, xd)   << '\n';
  t[1] = eve::tchebytchev(1, xd);
  std::cout << "-> t[1]                                    = " <<  t[1] << '\n';
  std::cout << "-> tchebytchev(" << 1 << ", xd)                      = " << eve::tchebytchev(1, xd)   << '\n';
   for(int i = 2; i <= 7; ++i)
  {
    t[i] = eve::tchebytchev[eve::successor](xd, t[i-1], t[i-2]);
    std::cout << "-> t[" << i << "]                                    = " <<  t[i] << '\n';
    std::cout << "-> tchebytchev(" << i << ", xd)                      = " << eve::tchebytchev(i, xd)   << '\n';
 }

}
