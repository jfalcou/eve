#include <boost/math/special_functions/expint.hpp>
#include <eve/function/expni.hpp>
#include <eve/wide.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{

  wide_ft pd = {0.5, 1.5, 0.1, 1.0, 19.0, 25.0, 21.5, 10000.0};
  wide_ft n  = {0, 1, 5, -2, 10, 6000, 0, 1.5};
  wide_ft r  = eve::expni(n, pd);

  std::cout << "---- simd" << '\n'
            << "<- pd           = " << pd << '\n'
            << "<- n            = " << n  << '\n'
            << "-> expni(n, pd) = " << r << '\n';

  float xd = 0.5f;

  std::cout << "---- scalar" << '\n'
            << "<- xd        = " << xd << '\n'
            << "-> expni(0, xd) = " << eve::expni(0, xd) << '\n';


  return 0;
}
