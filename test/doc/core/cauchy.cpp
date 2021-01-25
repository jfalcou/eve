#include <eve/function/cauchy.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<4>>;

int main()
{
  wide_ft x = { 0.0f, 1.0f, -1.0f, 5.0f };
  wide_ft p = { 0.0f, 0.5f, 0.75f, 1.0f };
  wide_ft m = { 0.0f, -1.0f, 1.0f, 2.0f };
  wide_ft s = { 1.0f,  2.0f, 3.0f, 4.0f };

  auto ca = eve::cauchy(m, s);

  std::cout
    << "---- simd" << '\n'
    << "<- x                   = " << x << '\n'
    << "<- m                   = " << m << '\n'
    << "<- s                   = " << s << '\n'
    << "<- p                   = " << p << '\n'
    << "-> median(ca)          = " << eve::median(ca) << '\n'
    << "-> mode(ca)            = " << eve::mode(ca) << '\n'
    << "-> fisher(ca)          = " << eve::fisher(ca) << '\n'
    << "-> pdf(ca, x)          = " << eve::pdf(ca, x) << '\n'
    << "-> invcdf(ca, p)       = " << eve::invcdf(ca, p)  << '\n'
    << "-> cdf(ca, x)          = " << eve::cdf(ca, x)  << '\n';

  auto [mm, ss] =  eve::parameters(ca);
  std::cout << "mm             = " << mm << std::endl;
  std::cout << "ss             = " << ss << std::endl;
  ;

  float xf = 9.0f;
  float mf = 10.0f;
  float sf = 2.0;
  auto caf = eve::cauchy(mf, sf);

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf                  = " << xf << '\n'
    << "<- mf                  = " << mf << '\n'
    << "<- sf                  = " << sf << '\n'
    << "-> cdf(caf, xf)        = " << eve::cdf(caf, xf) << '\n'
    << "-> mode(caf)           = " << eve::mode(caf)    << '\n';
  return 0;
}
