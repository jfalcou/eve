#include <eve/module/elliptic.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft pf = {1.0f, 0.1f, 0.75f, 0.5f};

  std::cout << "---- simd" << '\n'
            << "<- pf           = " << pf << '\n'
            << "-> ellint_d(pf) = " << eve::ellint_d(pf) << '\n';

  float xf = 0.1f;

  std::cout << "---- scalar" << '\n'
            << "<- xf            = " << xf << '\n'
            << "-> ellint_d(xf)  = " << eve::ellint_d(xf) << '\n';


    wide_ft phi = {0.2f, 1.0e-30f, 0.5f, 0.3f};
   std::cout << "---- simd" << '\n'
             << "<- phi               = " << phi << '\n'
             << "<- pf                = " << pf  << '\n'
             << "-> ellint_d(phi, pf) = " << eve::ellint_d(phi, pf) << '\n';

}
