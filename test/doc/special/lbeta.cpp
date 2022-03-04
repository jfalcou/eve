#include <eve/module/special.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<4>>;

int main()
{
  wide_ft pf = { 0.0f, 1.0f, 4.0f, 2.0f };
  wide_ft qf = { 1.0f, 1.0f, 3.0f, 5.0f};

  std::cout
    << "---- simd" << '\n'
    << "<- pf                      = " << pf << '\n'
    << "<- qf                      = " << qf << '\n'
    << "-> lbeta(pf, qf)           = " << eve::lbeta(pf, qf) << '\n'
    << "-> diff_1st(lbeta)(pf, qf) = " << eve::diff_1st(eve::lbeta)(pf, qf) << '\n'
    << "-> diff_2nd(lbeta)(pf, qf) = " << eve::diff_2nd(eve::lbeta)(pf, qf) << '\n';

  float xf = 2.0f;
  float yf = 10.0f;

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf             = " << xf << '\n'
    << "<- yf             = " << yf << '\n'
    << "-> lbeta(xf, yf)  = " << eve::lbeta(xf, yf) << '\n';
  return 0;
}
