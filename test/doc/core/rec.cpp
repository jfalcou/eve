#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{
  wide_ft pf = {0.0f, 1.0f, 2.0f, 10.0f, 200.0f, 1000.0f,
               eve::inf(eve::as<float>()), eve::nan(eve::as<float>())};

  std::cout << "---- simd" << '\n'
            << "<- pf                 = " << pf << '\n'
            << "-> rec[raw2](pf   )   = " << eve::rec[eve::raw2](pf) << '\n'
            << "-> rec(pf)            = " << eve::rec(pf) << '\n'
            << "-> rec[pedantic2](pf) = " << eve::rec[eve::raw2](pf) << '\n'
            << "-> rec[pf > 10][raw2](pf) = " << eve::rec[pf > 10][eve::raw2](pf) << '\n'
            << "-> rec[pf > 10](pf)    = " << eve::rec[pf > 10](pf) << '\n';

  float xf = 1.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf      = " << xf << '\n'
            << "-> rec(xf) = " << eve::rec(xf) << '\n';
  return 0;
}
