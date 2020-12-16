#include <eve/function/derivative/acotpi.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<4>>;

int main()
{
  wide_ft pf = { 0.0f, 1.0f, -1.0f, -0.5f};

  std::cout
    << "---- simd" << '\n'
    << "<- pf                   = " << pf << '\n'
    << "-> derivative(acotpi)(pf) = " << eve::derivative(eve::acotpi)(pf) << '\n';

  float xf = 1.0f;

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf                   = " << xf << '\n'
    << "-> derivative(acotpi)(xf) = " << eve::derivative(eve::acotpi)(xf) << '\n'; 
  return 0;
}
