#include <eve/function/diff/exp_int.hpp>
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
    << "-> diff(exp_int)(1, pf)  = " << eve::diff(eve::exp_int)(1, pf) << '\n'
    << "-> diff(exp_int)(i, pf)  = " << eve::diff(eve::exp_int)(i, pf) << '\n';

  float xf = 1.0f;

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf                   = " << xf << '\n'
    << "-> diff(exp_int)(xf) = " << eve::diff(eve::exp_int)(2, xf) << '\n';
  return 0;
}
