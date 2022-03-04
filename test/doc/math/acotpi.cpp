#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<4>>;

int main()
{
  wide_ft pf = { 0.0f, 2.0f, -1.0f, -0.5f};

  std::cout
    << "---- simd" << '\n'
    << "<- pf               = " << pf << '\n'
    << "-> acotpi(pf)       = " << eve::acotpi(pf) << '\n'
    << "-> diff(acotpi)(pf) = " << eve::diff(eve::acotpi)(pf) << '\n';

  float xf = 1.0f;
  float yf = eve::inf(eve::as<float>());

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf         = " << xf << '\n'
    << "-> acotpi(xf) = " << eve::acotpi(xf) << '\n'
    << "<- yf         = " << yf << '\n'
    << "-> acotpi(yf) = " << eve::acotpi(yf) << '\n';
  return 0;
}
