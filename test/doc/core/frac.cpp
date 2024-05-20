#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{
  wide_ft pf = {-1.0f, -1.3f, -0.0f, 0.0f,
                2.0f,  eve::prev(2.0f, 4), eve::inf(eve::as<float>()), eve::nan(eve::as<float>())};

  std::cout << "---- simd" << std::setprecision(8) << '\n'
            << "<- pf                         = " << pf << '\n'
            << "-> frac(pf)                   = " << eve::frac(pf) << '\n'
            << "-> frac[pf!=2.3f](pf)         = " << eve::frac[pf !=  2.3f](pf) << '\n'
            << "-> frac[pedantic](pf)         = " << eve::frac[eve::pedantic](pf)<< '\n'
            << "-> frac[raw](pf)              = " << eve::frac[eve::raw](pf)<< '\n'
            << "-> frac[almost](pf)           = " << eve::frac[eve::almost](pf)<< '\n'
            << "-> frac[almost = 1](pf)       = " << eve::frac[eve::almost = 1](pf)<< '\n'
            << "-> frac[almost][pedantic](pf) = " << eve::frac[eve::almost][eve::pedantic](pf)<< '\n'
    ;

  float xf = -327.68f;

  std::cout << "---- scalar" << std::setprecision(8) << '\n'
            << "<- xf             = " << xf << '\n'
            << "-> frac(xf)       = " << eve::frac(xf) << '\n';
  return 0;
}
