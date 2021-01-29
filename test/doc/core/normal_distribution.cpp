#include <eve/function/normal_distribution.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<4>>;

int main()
{
  wide_ft x = { 0.0f, 1.0f, -1.0f, 5.0f };
  wide_ft p = { 0.0f, 0.5f, 0.75f, 1.0f };
  wide_ft m = { 0.0f, -1.0f, 1.0f, 2.0f };
  wide_ft s = { 1.0f,  2.0f, 3.0f, 4.0f };

  auto no = eve::normal_distribution(m, s);

  std::cout
    << "---- simd" << '\n'
    << "<- x                   = " << x << '\n'
    << "<- m                   = " << m << '\n'
    << "<- s                   = " << s << '\n'
    << "<- p                   = " << p << '\n'
    << "-> median(no)          = " << eve::median(no) << '\n'
    << "-> mode(no)            = " << eve::mode(no) << '\n'
    << "-> mean(no)            = " << eve::mean(no) << '\n'
    << "-> var(no)             = " << eve::var(no) << '\n'
    << "-> entropy(no)          = " << eve::entropy(no) << '\n'
    << "-> pdf(no, x)          = " << eve::pdf(no, x) << '\n'
    << "-> invcdf(no, p)       = " << eve::invcdf(no, p)  << '\n'
    << "-> cdf(no, x)          = " << eve::cdf(no, x)  << '\n';

  float xf = 9.0f;
  float mf = 10.0f;
  float sf = 2.0;
  auto nof = eve::normal_distribution(mf, sf);

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf                  = " << xf << '\n'
    << "<- mf                  = " << mf << '\n'
    << "<- sf                  = " << sf << '\n'
    << "-> cdf(nof, xf)        = " << eve::cdf(nof, xf) << '\n'
    << "-> mode(nof)           = " << eve::mode(nof)    << '\n';
  return 0;
}
