#include <eve/module/special.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{

  wide_ft pf = {0.5, 1.5, 0.1, 1.0, 19.0, 25.0, 21.5, 10000.0};
  wide_ft n  = {0, 1, 5, -2, 10, 6000, 0, 1.5};

  std::cout << "---- simd" << '\n'
            << "<- pf                    = " << pf << '\n'
            << "<- n                     = " << n  << '\n'
            << "-> exp_int(n, pf)        = " << eve::exp_int(n, pf)  << '\n'
            << "-> exp_int(pf)           = " << eve::exp_int(pf) << '\n'
            << "-> diff(exp_int)(n, pf)  = " << eve::diff(eve::exp_int)(n, pf) << '\n';

  float xd = 0.5f;

  std::cout << "---- scalar" << '\n'
            << "<- xd             = " << xd << '\n'
            << "-> exp_int(1, xd) = " << eve::exp_int(1, xd) << '\n'
            << "-> exp_int(xd)    = " << eve::exp_int(xd) << '\n';

  return 0;
}
