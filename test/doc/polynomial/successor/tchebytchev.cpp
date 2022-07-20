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
  std::array<wide_ft, 8> t;
  t[0] = eve::tchebytchev(0, xd);
  std::cout << "-> t[0]          =  " <<  t[0] << '\n';
  std::cout << "-> tchebytchev(" << 0 << ", xd) = " << eve::tchebytchev(0, xd)   << '\n';
  t[1] = eve::tchebytchev(1, xd);
  std::cout << "-> tchebytchev(" << 1 << ", xd) = " << eve::tchebytchev(1, xd)   << '\n';
  std::cout << "-> t[1]          = " <<  t[1] << '\n';
   for(int i = 2; i <= 7; ++i)
  {
    t[i] = eve::successor(eve::tchebytchev)(xd, t[i-1], t[i-2]);
    std::cout << "-> t[" << i << "]           = " <<  t[i] << '\n';
    std::cout << "-> tchebytchev(" << i << ", xd) = " << eve::tchebytchev(i, xd)   << '\n';
 }
  return 0;
}
