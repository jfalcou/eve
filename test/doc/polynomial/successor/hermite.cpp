#include <eve/module/polynomial.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<double, eve::fixed<8>>;
using wide_it = eve::wide<int   , eve::fixed<8>>;

int main()
{

  wide_ft xd = {0.5, -1.5, 0.1, -1.0, 19.0, 25.0, 21.5, 10000.0};
  wide_it n = {0, 1, 2, 3, 4, 5, 6, 7};
  std::cout << "---- simd" << '\n'
            << "<- xd             = " << xd << '\n'
            << "<- n              = " << n  << '\n';
  std::array<wide_ft, 8> h;
  h[0] = eve::hermite(0, xd);
  std::cout << "-> h[0]          =  " <<  h[0] << '\n';
  std::cout << "-> hermite(" << 0 << ", xd) = " << eve::hermite(0, xd)   << '\n';
  h[1] = eve::hermite(1, xd);
  std::cout << "-> hermite(" << 1 << ", xd) = " << eve::hermite(1, xd)   << '\n';
  std::cout << "-> h[1]          = " <<  h[1] << '\n';
   for(int i = 2; i <= 7; ++i)
  {
    h[i] = eve::successor(eve::hermite)(i-1, xd, h[i-1], h[i-2]);
    std::cout << "-> h[" << i << "]           = " <<  h[i] << '\n';
    std::cout << "-> hermite(" << i << ", xd) = " << eve::hermite(i, xd)   << '\n';
 }
  return 0;
}
