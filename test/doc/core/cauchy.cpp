#include <eve/function/cauchy.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<4>>;

int main()
{
  wide_ft x = { 0.0f, 1.0f, -1.0f, 5.0f };
  wide_ft m = { 0.0f, -1.0f, 1.0f, -0.0f};
  wide_ft s = { 1.0f, 2.0f, 3.0f, 4.0f};

  auto c_cdf    = eve::cdf(eve::cauchy)(1.0, 2.0);
  auto c_pdf    = eve::pdf(eve::cauchy)(1.0, 2.0);
  auto c_invcdf = eve::invcdf(eve::cauchy)(1.0, 2.0);

  std::cout
    << "---- simd" << '\n'
    << "<- x                   = " << x << '\n'
    << "<- m                   = " << m << '\n'
    << "<- s                   = " << s << '\n'
    << "-> cauchy(x, m, s)     = " << eve::cauchy(x, m, s) << '\n'
    << "-> cauchy(x, m)        = " << eve::cauchy(x, m)    << '\n'
    << "-> cauchy(x)           = " << eve::cauchy(x)       << '\n'
    << "-> median(cauchy)(x)   = " << eve::median(eve::cauchy)(x) << '\n'
    << "-> mean(cauchy)(x)     = " << eve::mean(eve::cauchy)(x) << '\n'
    << "-> c_pdf(x)            = " << c_pdf(x) << '\n'
    << "-> c_invcdf(x)         = " << c_invcdf(x)  << '\n'
    << "-> c_cdf(x)            = " << c_cdf(x)  << '\n'
    << "-> cauchy(x, 1.0, 2.0) = " << eve::cauchy(x, 1.0, 2.0) << '\n';
   ;

  float xf = 9.0f;
  float mf = 10.0f;
  float sf = 2.0;

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf                  = " << xf << '\n'
    << "<- mf                  = " << mf << '\n'
    << "<- sf                  = " << sf << '\n'
    << "-> cauchy(xf, mf, sf)  = " << eve::cauchy(xf, mf, sf) << '\n';
  return 0;
}
