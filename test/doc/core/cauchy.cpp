#include <eve/function/cauchy.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<4>>;

int main()
{
  wide_ft x = { 0.0f, 1.0f, -1.0f, 5.0f };
  wide_ft m = { 0.0f, -1.0f, 1.0f, -0.0f};
  wide_ft s = { 1.0f, 2.0f, 3.0f, 4.0f};

  std::cout
    << "---- simd" << '\n'
    << "<- x               = " << x << '\n'
    << "<- m               = " << m << '\n'
    << "<- s               = " << s << '\n'
    << "-> cauchy(x, m, s) = " << eve::cauchy(x, m, s) << '\n'
    << "-> cauchy(x, m)    = " << eve::cauchy(x, m)    << '\n'
    << "-> cauchy(x)       = " << eve::cauchy(x)       << '\n';

  float xf = 9.0f;
  float mf = 10.0f;
  float sf = 2.0;

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf                 = " << xf << '\n'
    << "<- mf                 = " << mf << '\n'
    << "<- sf                 = " << sf << '\n'
    << "-> cauchy(xf, mf, sf) = " << eve::cauchy(xf, mf, sf) << '\n';
  return 0;
}
