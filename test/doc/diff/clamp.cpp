#include <eve/function/diff/clamp.hpp>
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
    << "-> diff_1st(clamp)(pf, qf, rf) = " << eve::diff_1st(eve::clamp)(pf, qf, rf) << '\n'
    << "-> diff_2nd(clamp)(pf, qf, rf) = " << eve::diff_2nd(eve::clamp)(pf, qf, rf) << '\n'
    << "-> diff_3rd(clamp)(pf, qf, rf) = " << eve::diff_3rd(eve::clamp)(pf, qf, rf) << '\n';


  float xf = 0.5f;
  float yf = 0.5f;
  float zf = 0.1f;
  std::cout
    << "---- scalar"  << '\n'
    << "<- xf                      = " << xf << '\n'
    << "<- yf                      = " << yf << '\n'
    << "<- zf                      = " << yf << '\n'
    << "-> diff_1st(clamp)(xf, yf, zf) = " << eve::diff_1st(eve::clamp)(xf, yf, zf) << '\n'
    << "-> diff_2nd(clamp)(xf, yf, zf) = " << eve::diff_2nd(eve::clamp)(xf, yf, zf) << '\n'
    << "-> diff_3rd(clamp)(xf, yf, zf) = " << eve::diff_3rd(eve::clamp)(xf, yf, zf) << '\n';
  return 0;
}
