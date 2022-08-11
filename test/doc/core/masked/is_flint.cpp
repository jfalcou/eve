#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{
  wide_ft pf = {0.0f, 1.0f, -1.5f, -2.0f, eve::valmax(eve::as<float>()),
                eve::inf(eve::as<float>()), eve::maxflint(eve::as<float>())*2, eve::nan(eve::as<float>())};

  std::cout << "---- simd" << '\n'
            << "<- pf                      = " << pf << '\n'
            << "-> is_flint[pf > 0](pf)    = " << eve::is_flint[pf > 0](pf) << '\n';
  return 0;
}
