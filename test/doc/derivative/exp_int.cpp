#include <eve/function/derivative/exp_int.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<4>>;
using wide_it = eve::wide <std::int32_t, eve::fixed<4>>;

int main()
{
  wide_ft pf = { 0.0f, 1.0f, 2.0f, 3.0f};
  wide_it i = { 0, 1, 2, 3};

  std::cout
    << "---- simd" << '\n'
    << "<- pf                          = " << pf << '\n'
    << "<- i                           = " << i << '\n'
    << "-> derivative(exp_int)(1, pf)  = " << eve::derivative(eve::exp_int)(1, pf) << '\n'
    << "-> derivative(exp_int)(i, pf)  = " << eve::derivative(eve::exp_int)(i, pf) << '\n';

  float xf = 1.0f;

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf                   = " << xf << '\n'
    << "-> derivative(exp_int)(xf) = " << eve::derivative(eve::exp_int)(2, xf) << '\n';
  return 0;
}
