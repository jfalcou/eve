#include <eve/function/uniform_continuous_distribution.hpp>
#include <eve/wide.hpp>
#include <iostream>


int main()
{
   using wide_dt = eve::wide <double, eve::fixed<4>>;
  wide_dt x = { 0.0f, 1.0f, 5.0f, 12.0f };
  wide_dt b = { 2, 3, 6, 20 };
  wide_dt a = { -2, 0, 3, 4};

//   using wide_dt = eve::wide <float, eve::fixed<4>>;
//   using wide_it = eve::wide <std::int32_t, eve::fixed<4>>;
//   wide_dt x = { 0.0f, 1.0f, 5.0f, 12.0f };
//   wide_it b = { 2, 3, 6, 20 };
//   wide_it a = { -2, 0, 3, 4};

  auto d = eve::uniform_continuous_distribution(a,  b); //, eve::as<double>());

  std::cout
    << "---- simd with wide double initialization continuous distribution" << '\n'
    << "<- x                  = " << x << '\n'
    << "<- a                  = " << d.a << '\n'
    << "<- b                  = " << d.b << '\n'
    << "-> median(d)          = " << eve::median(d) << '\n'
    << "-> mode(d)            = " << eve::mode(d) << '\n'
    << "-> mean(d)            = " << eve::mean(d) << '\n'
    << "-> var(d)             = " << eve::var(d) << '\n'
    << "-> entropy(d)         = " << eve::entropy(d) << '\n'
    << "-> pdf(d, x)          = " << eve::pdf(d, x) << '\n'
    << "-> cdf(d, x)          = " << eve::cdf(d, x)  << '\n'
    << "-> mgf(d, x)          = " << eve::mgf(d, x)  << '\n';
  return 0;
}
