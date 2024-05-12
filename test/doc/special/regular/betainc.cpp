#include <eve/module/special.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<4>>;

int main()
{
  wide_ft pf = { 0.0f, 0.1f, 0.5f, 2.0f};
  wide_ft qf = { 1.0f, 1.0f, 3.0f, 5.0f};
  wide_ft rf = { 4.0f, 2.0f, 1.0f, 0.2f};

  std::cout
    << "---- simd" << '\n'
    << "<- pf                   = " << pf << '\n'
    << "<- qf                   = " << qf << '\n'
    << "<- rf                   = " << rf << '\n'
    << "-> betainc(pf, qf, rf)  = " << eve::betainc(pf, qf, rf) << '\n'
    ;

  float xf = 0.2f;
  float yf = 0.5f;
  float zf = 2.0f;

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf                   = " << xf << '\n'
    << "<- yf                   = " << yf << '\n'
    << "<- zf                   = " << zf << '\n'
    << "-> betainc(xf, yf, zf)  = " << eve::betainc(xf, yf, zf) << '\n';
  return 0;
}
