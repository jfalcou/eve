#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<double, eve::fixed<8>>;

int main()
{
  wide_ft p = {14, 1, 3, 8, 20, 23000, 0, 48};

  std::cout << "---- simd" << '\n'
            << "<- p      = " << p << '\n'
            << "-> ufp(p) = " << eve::ufp(p) << '\n';

  double xf = 48;

  std::cout << "---- scalar" << '\n'
            << "<- xf      = " << xf << '\n'
            << "-> ufp(xf) = " << eve::ufp(xf) << '\n';
  return 0;
}
