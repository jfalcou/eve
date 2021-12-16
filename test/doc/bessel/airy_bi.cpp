//#include <eve/function/airy_bi.hpp>
#include <eve/module/bessel.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<double, eve::fixed<8>>;

int main()
{

  wide_ft pd = {0.5, -1.5, 0.1, -1.0, 19.0, 25.0, 21.5, 10.0};
  std::cout << "---- simd" << '\n'
            << "<- pd          = " << pd << '\n'
            << "-> airy_bi(pd) = " << eve::airy_bi(pd) << '\n';


  double xd = -1.0;

  std::cout << "---- scalar" << '\n'
            << "<- xd          = " << xd << '\n'
            << "-> airy_bi(xd) = " << eve::airy_bi(xd) << '\n';


  return 0;
}
