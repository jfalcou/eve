#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{
  wide_ft pf = {-1.0f, -1.3f, -0.0f, 0.0f,
                 2.0f,  2.3f, eve::inf(eve::as<float>()), eve::nan(eve::as<float>())};

  std::cout << "---- simd" << '\n'
            << "<- pf             = " << pf << '\n'
            << "-> frac[pf !=  2.3f](pf)       = " << eve::frac[pf !=  2.3f](pf) << '\n';
  return 0;
}
