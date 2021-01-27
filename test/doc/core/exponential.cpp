#include <eve/function/exponential.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<4>>;

int main()
{
  wide_ft x = { 0.0f, 1.0f, -1.0f, 5.0f };
  wide_ft p = { 0.0f, 0.5f, 0.75f, 1.0f };
  wide_ft lambda = { 1.0f,  2.0f, 3.0f, 4.0f };

  auto ex = eve::exponential<wide_ft>(lambda);

  std::cout
    << "---- simd" << '\n'
    << "<- x                   = " << x << '\n'
    << "<- lambda              = " << lambda << '\n'
    << "<- p                   = " << p << '\n'
    << "-> median(ex)          = " << eve::median(ex) << '\n'
    << "-> mean(ex)            = " << eve::mean(ex) << '\n'
    << "-> mode(ex)            = " << eve::mode(ex) << '\n'
    << "-> stdev(ex)           = " << eve::stdev(ex) << '\n'
    << "-> var(ex)             = " << eve::var(ex) << '\n'
    << "-> fisher(ex)          = " << eve::fisher(ex) << '\n'
    << "-> skewness(ex)        = " << eve::skewness(ex) << '\n'
    << "-> kurtosis(ex)        = " << eve::kurtosis(ex) << '\n'
    << "-> pdf(ex, x)          = " << eve::pdf(ex, x) << '\n'
    << "-> invcdf(ex, p)       = " << eve::invcdf(ex, p)  << '\n'
    << "-> cdf(ex, x)          = " << eve::cdf(ex, x)  << '\n'
    << "-> mgf(ex, x)          = " << eve::mgf(ex, x)  << '\n';

  float xf = 9.0f;
  float lf = 10.0f;
  auto exf = eve::exponential<float>(lf);

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf                  = " << xf << '\n'
    << "<- lf                  = " << lf << '\n'
    << "-> cdf(exf, xf)        = " << eve::cdf(exf, xf) << '\n'
    << "-> mode(exf)           = " << eve::mode(exf)    << '\n';
  return 0;
}
