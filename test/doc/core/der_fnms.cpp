#include <eve/function/derivative/fnms.hpp>
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
    << "-> derivative_1st(fnms)(pf, qf, rf) = " << eve::derivative_1st(eve::fnms)(pf, qf, rf) << '\n'
    << "-> derivative_2nd(fnms)(pf, qf, rf) = " << eve::derivative_2nd(eve::fnms)(pf, qf, rf) << '\n'
    << "-> derivative_3rd(fnms)(pf, qf, rf) = " << eve::derivative_3rd(eve::fnms)(pf, qf, rf) << '\n';


  float xf = 0.5f;
  float yf = 0.5f;
  float zf = 0.1f;
  std::cout
    << "---- scalar"  << '\n'
    << "<- xf                      = " << xf << '\n'
    << "<- yf                      = " << yf << '\n'
    << "<- zf                      = " << yf << '\n'
    << "-> derivative_1st(fnms)(xf, yf, zf) = " << eve::derivative_1st(eve::fnms)(xf, yf, zf) << '\n'
    << "-> derivative_2nd(fnms)(xf, yf, zf) = " << eve::derivative_2nd(eve::fnms)(xf, yf, zf) << '\n'
    << "-> derivative_3rd(fnms)(xf, yf, zf) = " << eve::derivative_3rd(eve::fnms)(xf, yf, zf) << '\n';
  return 0;
}
