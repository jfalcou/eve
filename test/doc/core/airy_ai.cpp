#include <eve/function/airy_ai.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<double, eve::fixed<8>>;

int main()
{

  wide_ft pd = {0.5, -1.5, 0.1, -1.0, 19.0, 25.0, 21.5, 10000.0};
  std::cout << "---- simd" << '\n'
            << "<- pd          = " << pd << '\n'
            << "-> airy_ai(pd) = " << eve::airy_ai(pd) << '\n';


  double xd = -1.0;

  std::cout << "---- scalar" << '\n'
            << "<- xd          = " << xd << '\n'
            << "-> airy_ai(xd) = " << eve::airy_ai(xd) << '\n';


  return 0;
}
