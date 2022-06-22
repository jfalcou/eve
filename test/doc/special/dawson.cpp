#include <eve/module/special.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{

  wide_ft pf = {0.0f, -0.0f, -1.0f, 1.0f, 2.0f,
               eve::inf(eve::as<float>()), eve::minf(eve::as<float>()), eve::nan(eve::as<float>())};

  std::cout << "---- simd" << '\n'
            << "<- pf               = " << pf << '\n'
            << "-> dawson(pf)       = " << eve::dawson(pf) << '\n'
            ;

  float xf = 1.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf         = " << xf << '\n'
            << "-> dawson(xf) = " << eve::dawson(xf) << '\n';
  return 0;
}
