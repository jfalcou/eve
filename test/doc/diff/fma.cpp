#include <eve/function/diff/fma.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<4>>;

int main()
{
  wide_ft pf = { 0.0f, 1.0f, -1.0f, -0.5f};
  wide_ft qf = { 1.0f, -1.0f, -0.5f, 0.0f};
  wide_ft rf = { 1.0f, 2.0f, -5.0f, 0.1f};

  std::cout
    << "---- simd" << '\n'
    << "<- pf                          = " << pf << '\n'
    << "<- qf                          = " << qf << '\n'
    << "<- rf                          = " << rf << '\n'
    << "-> diff_1st(fma)(pf, qf, rf) = " << eve::diff_1st(eve::fma)(pf, qf, rf) << '\n'
    << "-> diff_2nd(fma)(pf, qf, rf) = " << eve::diff_2nd(eve::fma)(pf, qf, rf) << '\n'
    << "-> diff_3rd(fma)(pf, qf, rf) = " << eve::diff_3rd(eve::fma)(pf, qf, rf) << '\n';


  float xf = 0.5f;
  float yf = 0.5f;
  float zf = 0.1f;
  std::cout
    << "---- scalar"  << '\n'
    << "<- xf                      = " << xf << '\n'
    << "<- yf                      = " << yf << '\n'
    << "<- zf                      = " << yf << '\n'
    << "-> diff_1st(fma)(xf, yf, zf) = " << eve::diff_1st(eve::fma)(xf, yf, zf) << '\n'
    << "-> diff_2nd(fma)(xf, yf, zf) = " << eve::diff_2nd(eve::fma)(xf, yf, zf) << '\n'
    << "-> diff_3rd(fma)(xf, yf, zf) = " << eve::diff_3rd(eve::fma)(xf, yf, zf) << '\n';
  return 0;
}
