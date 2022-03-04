#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<4>>;

int main()
{
  wide_ft pf = { 0.0f, 1.0f, 4.0f, -2.0f };
  wide_ft qf = { 1.0f, -1.0f, 3.0f, -0.0f};

  std::cout
    << "---- simd" << '\n'
    << "<- pf                      = " << pf << '\n'
    << "<- qf                      = " << qf << '\n'
    << "-> atan2(pf, qf)           = " << eve::atan2(pf, qf) << '\n'
    << "-> diff_1st(atan2)(pf, qf) = " << eve::diff_1st(eve::atan2)(pf, qf) << '\n'
    << "-> diff_2nd(atan2)(pf, qf) = " << eve::diff_2nd(eve::atan2)(pf, qf) << '\n';

  float xf = 2.0f;
  float yf = 10.0f;

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf            = " << xf << '\n'
    << "-> atan2(xf, yf) = " << eve::atan2(xf, yf) << '\n';
  return 0;
}
