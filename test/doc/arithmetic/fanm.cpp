#include <eve/function/diff/fanm.hpp>
#include <eve/module/arithmetic.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<4>>;

int main()
{
  wide_ft rf = { 0.0f, 1.0f, -1.0f, -0.5f};
  wide_ft qf = { 1.0f, -1.0f, -0.5f, 0.0f};
  wide_ft pf = { 1.0f, 2.0f, -5.0f, 0.1f};

  std::cout
    << "---- simd" << '\n'
    << "<- pf                          = " << pf << '\n'
    << "<- qf                          = " << qf << '\n'
    << "<- rf                          = " << rf << '\n'
    << "-> fanm(pf, qf, rf)            = " << eve::fanm(pf, qf, rf) << '\n'
    << "-> diff_1st(fanm)(pf, qf, rf)  = " << eve::diff_1st(eve::fanm)(pf, qf, rf) << '\n'
    << "-> diff_2nd(fanm)(pf, qf, rf)  = " << eve::diff_2nd(eve::fanm)(pf, qf, rf) << '\n'
    << "-> diff_3rd(fanm)(pf, qf, rf)  = " << eve::diff_3rd(eve::fanm)(pf, qf, rf) << '\n';


  float xf = 1.0f;
  float yf = 0.5f;
  float zf = 0.5f;
  std::cout
    << "---- scalar"  << '\n'
    << "<- xf                         = " << xf << '\n'
    << "<- yf                         = " << yf << '\n'
    << "<- zf                         = " << yf << '\n'
    << "-> fanm(xf, yf, zf)           = " << eve::fanm(xf, yf, zf) << '\n'
    << "-> diff_1st(fanm)(xf, yf, zf) = " << eve::diff_1st(eve::fanm)(xf, yf, zf) << '\n'
    << "-> diff_2nd(fanm)(xf, yf, zf) = " << eve::diff_2nd(eve::fanm)(xf, yf, zf) << '\n'
    << "-> diff_3rd(fanm)(xf, yf, zf) = " << eve::diff_3rd(eve::fanm)(xf, yf, zf) << '\n';
  return 0;
}
