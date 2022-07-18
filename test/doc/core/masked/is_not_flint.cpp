#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{
  wide_ft pf = {0.0f, 1.0f, -1.5f, -2.0f, eve::valmax(eve::as<float>()),
                eve::inf(eve::as<float>()), eve::maxflint(eve::as<float>())*2, eve::nan(eve::as<float>())};

  std::cout << "---- simd" << '\n'
            << "<- pf                          = " << pf << '\n'
            << "-> is_not_flint(pf)            = " << eve::is_not_flint(pf) << '\n'
            << "-> pedantic(is_not_flint)(pf)  = " << eve::pedantic(eve::is_not_flint)(pf) << '\n'  ;

  float xf = 1.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf                          = " << xf << '\n'
            << "-> is_not_flint(xf)            = " << eve::is_not_flint(xf) << '\n';
  return 0;
}
