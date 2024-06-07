#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;

consteval auto constexpr_is_flint(auto a) { return eve::is_flint(a); }

int main()
{
  wide_ft pf = {0.0f, 1.0f, -1.5f, -2.0f, eve::valmax(eve::as<float>()),
                eve::inf(eve::as<float>()), eve::maxflint(eve::as<float>())*2, eve::nan(eve::as<float>())};

  std::cout << "---- simd" << '\n'
            << "<- pf                      = " << pf << '\n'
            << "-> is_flint(pf)            = " << eve::is_flint(pf) << '\n'
            << "-> is_flint[pedantic](pf)  = " << eve::is_flint[eve::pedantic](pf) << '\n'
            << "-> is_flint[pf>0](pf)      = " << eve::is_flint[pf>0](pf) << '\n';

  float xf = 1.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf                      = " << xf << '\n'
            << "-> is_flint(xf)            = " << eve::is_flint(xf) << '\n';

//  std::cout << "-> constexpr_is_flint(1.0f) = " << constexpr_is_flint(1.0f) << std::endl;

  return 0;
}
