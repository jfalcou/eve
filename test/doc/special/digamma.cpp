//#include <eve/function/digamma.hpp>
#include <eve/module/special.hpp>
#include <eve/wide.hpp>
#include <eve/module/core/constant/inf.hpp>
#include <eve/module/core/constant/minf.hpp>
#include <eve/module/core/constant/nan.hpp>
#include <iostream>

using wide_ft = eve::wide<double, eve::fixed<8>>;

int main()
{

  wide_ft pd = {0.5, -1.5, 0.1, -1.0, 19.0, 25.0, 21.5, 10000.0};
  std::cout << "---- simd" << '\n'
            << "<- pd        = " << pd << '\n'
            << "-> digamma(pd) = " << eve::digamma(pd) << '\n';


  double xd = -1.0;

  std::cout << "---- scalar" << '\n'
            << "<- xd        = " << xd << '\n'
            << "-> digamma(xd) = " << eve::digamma(xd) << '\n';


  return 0;
}
