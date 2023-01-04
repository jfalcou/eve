#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<4>>;

int main()
{
  wide_ft pf = { 0.0f, 1.0f, -1.0f, -0.5f};

  std::cout
    << "---- simd" << '\n'
    << "<- pf            = " << pf << '\n'
    
    << "-> eve::arg(pf)  = " << eve::arg(pf) << '\n';

  float xf = 1.0f;
  float yf = eve::nan(eve::as<float>());

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf            = " << xf << '\n'
    << "-> eve::arg(xf)  = " << eve::arg(xf) << '\n'
    << "<- yf            = " << yf << '\n'
    << "-> eve::arg(yf)  = " << eve::arg(yf) << '\n';
  return 0;
}
