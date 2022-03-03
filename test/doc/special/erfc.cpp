#include <eve/module/special.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{

  wide_ft pf = {0.5f, -1.5f, -1.0f, 1.0f, 2.0f,
               eve::inf(eve::as<float>()), eve::minf(eve::as<float>()), eve::nan(eve::as<float>())};

  std::cout << "---- simd" << '\n'
            << "<- pf              = " << pf << '\n'
            << "-> erfc(pf)        = " << eve::erfc(pf) << '\n'
            << "-> diff(erfc)(pf)  = " << eve::diff(eve::erfc)(pf) << '\n';

  float xf = 4.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf              = " << xf << '\n'
            << "-> erfc(xf)        = " << eve::erfc(xf) << '\n';

  return 0;
}
