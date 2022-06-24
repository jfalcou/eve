#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<4>>;

int main()
{
  wide_ft pf = { 0.0f, 0.99f, -1.0f, -0.5f};

  std::cout
    << "---- simd" << '\n'
    << "<- pf                 = " << pf << '\n'
    << "-> acos(pf)           = " << eve::acos(pf) << '\n'
    ;

  float xf = 1.0f;
  float yf = eve::nan(eve::as<float>());

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf            = " << xf << '\n'
    << "-> eve::acos(xf) = " << eve::acos(xf) << '\n'
    << "<- yf            = " << yf << '\n'
    << "-> eve::acos(yf) = " << eve::acos(yf) << '\n';
  return 0;
}
