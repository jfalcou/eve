#include <eve/function/diff/acosh.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<4>>;

int main()
{
  wide_ft pf = { 0.0f, 1.0f, -1.0f, -0.5f};

  std::cout
    << "---- simd" << '\n'
    << "<- pf                   = " << pf << '\n'
    << "-> diff(acosh)(pf) = " << eve::diff(eve::acosh)(pf) << '\n';

  float xf = 1.0f;

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf                   = " << xf << '\n'
    << "-> diff(acosh)(xf) = " << eve::diff(eve::acosh)(xf) << '\n';
  return 0;
}
