#include <eve/function/binomial_distribution.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<4>>;

int main()
{
  wide_ft x = { 0.0f, 1.0f, 3.0f, 5.0f };
  wide_ft n = { 2.0f, 3.0f, 6.0, 20.0f };
  wide_ft p = { 0.1f, 0.5f, 0.75, 0.9f };

  auto bi = eve::binomial_distribution(n,  p);

  std::cout
    << "---- simd" << '\n'
    << "<- x                   = " << x << '\n'
    << "<- n                   = " << n << '\n'
    << "<- p                   = " << p << '\n'
    << "-> median(bi)          = " << eve::median(bi) << '\n'
    << "-> mode(bi)            = " << eve::mode(bi) << '\n'
    << "-> mean(bi)            = " << eve::mean(bi) << '\n'
    << "-> var(bi)             = " << eve::var(bi) << '\n'
    << "-> entropy(bi)         = " << eve::entropy(bi) << '\n'
    << "-> pmf(bi, x)          = " << eve::pmf(bi, x) << '\n'
    << "-> cdf(bi, x)          = " << eve::cdf(bi, x)  << '\n'
    << "-> mgf(bi, x)          = " << eve::mgf(bi, x)  << '\n';

  float xf = 9.0f;
  float mf = 10.0f;
  float sf = 0.5;
  auto bif = eve::binomial_distribution(mf, sf);

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf                  = " << xf << '\n'
    << "<- mf                  = " << mf << '\n'
    << "<- sf                  = " << sf << '\n'
    << "-> cdf(bif, xf)        = " << eve::cdf(bif, xf) << '\n'
    << "-> mode(bif)           = " << eve::mode(bif)    << '\n';
  return 0;
}
