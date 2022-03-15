#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<4>>;

int main()
{
  wide_ft pf = { 0.0f, 2.0f, -1.0f, -0.5f};

  std::cout
    << "---- simd" << '\n'
    << "<- pf        = " << pf << '\n'
    << "-> acotd(pf) = " << eve::acotd(pf) << '\n'
    << "-> diff(acotd)(pf) = " << eve::diff(eve::acotd)(pf) << '\n';

  float xf = 1.0f;
  float yf = eve::inf(eve::as<float>());

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf        = " << xf << '\n'
    << "-> acotd(xf) = " << eve::acotd(xf) << '\n'
    << "<- yf        = " << yf << '\n'
    << "-> acotd(yf) = " << eve::acotd(yf) << '\n';
  return 0;
}
