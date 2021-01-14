#include <eve/function/diff/beta.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<4>>;

int main()
{
  wide_ft pf = { 0.0f, 1.0f, -1.0f, -0.5f};
  wide_ft qf = { 1.0f, -1.0f, -0.5f, 0.0f};

  std::cout
    << "---- simd" << '\n'
    << "<- pf                   = " << pf << '\n'
    << "<- qf                   = " << qf << '\n'
    << "-> diff(beta)(pf, qf) = " << eve::diff(eve::beta)(pf, qf) << '\n';

  float xf = 0.5f;
  float yf = 0.5f;

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf                   = " << xf << '\n'
    << "<- yf                   = " << yf << '\n'
    << "-> diff(beta)(xf, yf) = " << eve::diff(eve::beta)(xf, yf) << '\n';
  return 0;
}
