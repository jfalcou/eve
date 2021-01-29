#include <eve/function/unif.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_dt = eve::wide <double, eve::fixed<4>>;

int main()
{
  wide_dt x = { 0.0f, 1.0f, 5.0f, 12.0f };
  wide_dt b = { 2.0f, 3.0f, 6.0, 20.0f };
  wide_dt a = { 0.1f, 0.5f, 3.75, 10.0f };

  auto d = eve::unif(a,  b);

  std::cout
    << "---- simd" << '\n'
    << "<- x                  = " << x << '\n'
    << "<- a                  = " << a << '\n'
    << "<- b                  = " << b << '\n'
    << "-> median(d)          = " << eve::median(d) << '\n'
    << "-> mode(d)            = " << eve::mode(d) << '\n'
    << "-> mean(d)            = " << eve::mean(d) << '\n'
    << "-> var(d)             = " << eve::var(d) << '\n'
    << "-> entropy(d)         = " << eve::entropy(d) << '\n'
    << "-> pdf(d, x)          = " << eve::pdf(d, x) << '\n'
    << "-> cdf(d, x)          = " << eve::cdf(d, x)  << '\n'
    << "-> mgf(d, x)          = " << eve::mgf(d, x)  << '\n';

  float xf = 9.0f;
  float bf = 10.0f;
  float af = 0.5f;
  auto df = eve::unif(af, bf);

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf                  = " << xf << '\n'
    << "<- af                  = " << af << '\n'
    << "<- bf                  = " << bf << '\n'
    << "-> cdf(df, xf)        = " << eve::cdf(df, xf) << '\n'
    << "-> pdf(df, xf)        = " << eve::pdf(df, xf) << '\n'
    << "-> mgf(df, 2.0f)      = " << eve::mgf(df, 2.0f) << '\n'
    << "-> mean(df)           = " << eve::mode(df)    << '\n'
    << "-> mode(df)           = " << eve::mode(df)    << '\n';

  return 0;
}
