#include <eve/function/derivative/tanpi.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<4>>;

int main()
{
  wide_ft pf = { 0.0f, 1.0f, -1.0f, -0.25f};

  std::cout
    << "---- simd" << '\n'
    << "<- pf                   = " << pf << '\n'
    << "-> derivative(tanpi)(pf) = " << eve::derivative(eve::tanpi)(pf) << '\n';

  float xf = 0.25f;

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf                   = " << xf << '\n'
    << "-> derivative(tanpi)(xf) = " << eve::derivative(eve::tanpi)(xf) << '\n';
  return 0;
}
