#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{
  wide_ft p = {14, 1, 3, eve::smallestposval(eve::as<float>()), 20, 23000, 0, 27};

  std::cout << "---- simd" << std::hexfloat << '\n'
            << "<- p                  = " << p << '\n'
            << "-> ulp(p)             = " << eve::ulp(p) << '\n'
            << "-> p-ulp(p)           = " << (p-eve::ulp(p)) << '\n'
            << "-> prev(p)            = " << eve::prev(p) << '\n'
            << "-> next(p)            = " << eve::next(p) << '\n';

  double xf = 48;

  std::cout << "---- scalar" << '\n'
            << "<- xf      = " << xf << '\n'
            << "-> ulp(xf) = " << eve::ulp(xf) << '\n';
  return 0;
}
