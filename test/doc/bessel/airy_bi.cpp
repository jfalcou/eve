#include <eve/module/bessel.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<double, eve::fixed<8>>;

int main()
{

  wide_ft pf = {0.5, -1.5, 0.1, -1.0, 19.0, 25.0, 21.5, 10.0};
  std::cout << "---- simd" << '\n'
            << "<- pf          = " << pf << '\n'
            << "-> airy_bi(pf) = " << eve::airy_bi(pf) << '\n'
            << "-> diff(airy_bi)(pf)  = " << eve::diff(eve::airy_bi)(pf) << '\n';


  double xd = -1.0;

  std::cout << "---- scalar" << '\n'
            << "<- xd          = " << xd << '\n'
            << "-> airy_bi(xd) = " << eve::airy_bi(xd) << '\n';


  return 0;
}
