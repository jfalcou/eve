#include <eve/function/derivative/tand.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<4>>;

int main()
{
  wide_ft pf = { 0.0f, 1.0f, -1.0f, -0.5f};

  std::cout
    << "---- simd" << '\n'
    << "<- pf                   = " << pf << '\n'
    << "-> derivative(tand)(pf) = " << eve::derivative(eve::tand)(pf) << '\n';

  float xf = 1.0f;

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf                   = " << xf << '\n'
    << "-> derivative(tand)(xf) = " << eve::derivative(eve::tand)(xf) << '\n'; 
  return 0;
}
