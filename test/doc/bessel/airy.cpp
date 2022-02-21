#include <eve/module/bessel.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<double, eve::fixed<8>>;

int main()
{

  wide_ft pd = {0.5, -1.5, 0.1, -1.0, 19.0, 25.0, 21.5, 10000.0};
  auto [ai, bi] = eve::airy(pd);
  std::cout << "---- simd" << '\n'
            << "<- pd  = " << pd << '\n'
            << "-> ai  = " << ai << '\n'
            << "-> bi  = " << bi << '\n';


  double xd = -1.0;
  auto [a, b] = eve::airy(xd);

  std::cout << "---- scalar" << '\n'
            << "<- xd = " << xd << '\n'
            << "-> a  = " << a << '\n'
            << "-> b  = " << b << '\n';


  return 0;
}
