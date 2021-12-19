//#include <eve/include/function/ellint_2.hpp>
#include <eve/module/elliptic.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/wide.hpp>
#include <eve/as.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft pf = {1.0f, 0.0f, 0.75f, 0.5f};

  std::cout << "---- simd" << '\n'
            << "<- pf           = " << pf << '\n'
            << "-> ellint_2(pf) = " << eve::ellint_2(pf) << '\n';

  float xf = 0.1f;

  std::cout << "---- scalar" << '\n'
            << "<- xf            = " << xf << '\n'
            << "-> ellint_2(xf,) = " << eve::ellint_2(xf) << '\n';


   wide_ft phi = {0.2f, 1.0e-30f, 0.5f, 0.0f};
   std::cout << "---- simd" << '\n'
             << "<- phi               = " << phi << '\n'
             << "-> ellint_2(phi, pf) = " << eve::ellint_2(phi, pf) << '\n'
             << "-> ellint_2(pio2,pf) = " << eve::ellint_2(eve::pio_2(eve::as(phi)), pf) << '\n';

  return 0;
}
