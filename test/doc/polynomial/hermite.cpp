// revision 0
#include <eve/module/polynomial.hpp>
#include <iostream>
#include <array>

int main()
{
  eve::wide xd = {0.5, -1.5, 0.1, -1.0, 19.0, 25.0, 21.5, 10000.0};
  eve::wide n  = {0, 1, 2, 3, 4, 5, 6, 7};
  eve::wide x(2.0);

  std::cout << "<- xd                             = " << xd << "\n";
  std::cout << "<- n                              = " << n << "\n";

  std::cout << "-> hermite(n, xd)                 = " << eve::hermite(n, xd) << "\n";
  std::cout << "-> hermite[ignore_last(2)](n, xd) = " << eve::hermite[eve::ignore_last(2)](n, xd) << "\n";
  std::cout << "-> hermite[n != 4](n, xd)         = " << eve::hermite[n != 4](n, xd) << "\n\n";

  using wide_ft =  decltype(xd);
  std::array<wide_ft, 8> h;
  h[0] = eve::hermite(0, xd);
  std::cout << "-> h[0]                           = " <<  h[0] << '\n';
  std::cout << "-> hermite(" << 0 << ", xd)                 = " << eve::hermite(0, xd)   << '\n';
  h[1] = eve::hermite(1, xd);
  std::cout << "-> hermite(" << 1 << ", xd)                 = " << eve::hermite(1, xd)   << '\n';
  std::cout << "-> h[1]                           = " <<  h[1] << '\n';
  for(int i = 2; i <= 7; ++i)
  {
    h[i] = eve::hermite[eve::successor](i-1, xd, h[i-1], h[i-2]);
    std::cout << "-> h[" << i << "]                           = " <<  h[i] << '\n';
    std::cout << "-> hermite(" << i << ", xd)                 = " << eve::hermite(i, xd)   << '\n';
 }
}
