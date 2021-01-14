#include <eve/function/diff/tanpi.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<4>>;

int main()
{
  wide_ft pf = { 0.0f, 1.0f, -1.0f, -0.25f};

  std::cout
    << "---- simd" << '\n'
    << "<- pf                   = " << pf << '\n'
    << "-> diff(tanpi)(pf) = " << eve::diff(eve::tanpi)(pf) << '\n';

  float xf = 0.25f;

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf                   = " << xf << '\n'
    << "-> diff(tanpi)(xf) = " << eve::diff(eve::tanpi)(xf) << '\n';
  return 0;
}
