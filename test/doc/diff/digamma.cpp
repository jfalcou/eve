#include <eve/function/diff/digamma.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<4>>;

int main()
{
  wide_ft pf = { 0.0f, 1.0f, -1.0f, -0.5f};

  std::cout
    << "---- simd" << '\n'
    << "<- pf                   = " << pf << '\n'
    << "-> diff(digamma)(pf) = " << eve::diff(eve::digamma)(pf) << '\n';

  float xf = 1.0f;

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf                   = " << xf << '\n'
    << "-> diff(digamma)(xf) = " << eve::diff(eve::digamma)(xf) << '\n';
  return 0;
}
