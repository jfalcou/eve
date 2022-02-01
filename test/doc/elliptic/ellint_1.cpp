//#include <eve/include/function/ellint_1.hpp>
#include <eve/module/elliptic.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <eve/module/math/constant/pio_2.hpp>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft pf = {1.0f, 0.0f, 0.75f, 0.5f};

  std::cout << "---- simd" << '\n'
            << "<- pf           = " << pf << '\n'
            << "-> ellint_1(pf) = " << eve::ellint_1(pf) << '\n';

  float xf = 0.1f;

  std::cout << "---- scalar" << '\n'
            << "<- xf            = " << xf << '\n'
            << "-> ellint_1(xf,) = " << eve::ellint_1(xf) << '\n';


   wide_ft phi = {0.2f, 1.0e-30f, 0.5f, 0.0f};
   std::cout << "---- simd" << '\n'
             << "<- phi               = " << phi << '\n'
             << "-> ellint_1(phi, pf) = " << eve::ellint_1(phi, pf) << '\n'
             << "-> ellint_1(pio2,pf) = " << eve::ellint_1(eve::pio_2(eve::as(phi)), pf) << '\n';

  return 0;
}
