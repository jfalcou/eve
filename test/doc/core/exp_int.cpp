#include <boost/math/special_functions/expint.hpp>
#include <eve/function/exp_int.hpp>
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
  wide_ft r  = eve::exp_int(n, pd);
  wide_ft r0 = eve::exp_int(pd);

  std::cout << "---- simd" << '\n'
            << "<- pd             = " << pd << '\n'
            << "<- n              = " << n  << '\n'
            << "-> exp_int(n, pd) = " << r  << '\n'
            << "-> exp_int(pd)    = " << r0 << '\n';

  float xd = 0.5f;

  std::cout << "---- scalar" << '\n'
            << "<- xd             = " << xd << '\n'
            << "-> exp_int(1, xd) = " << eve::exp_int(1, xd) << '\n'
            << "-> exp_int(xd)    = " << eve::exp_int(xd) << '\n';


  return 0;
}
