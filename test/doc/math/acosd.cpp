#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<4>>;

int main()
{
  wide_ft pf = { 0.0f, 1.0f, -1.0f, -0.5f};

  std::cout
    << "---- simd" << '\n'
    << "<- pf              = " << pf << '\n'
    << "-> eve::acosd(pf)  = " << eve::acosd(pf) << '\n'
    << "-> diff(acosd)(pf) = " << eve::diff(eve::acosd)(pf) << '\n';

  float xf = 1.0f;

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf             = " << xf << '\n'
    << "-> eve::acosd(xf) = " << eve::acosd(xf) << '\n';

  return 0;
}
