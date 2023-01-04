#include <eve/module/complex.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<4>>;

int main()
{
  wide_ft r = { 0.0f, 1.0f, 2.0f, 3.9f};
  wide_ft t = { eve::pio_2(eve::as(1.0f)), 0.0f, 1.0f, eve::nan(eve::as(1.0f))};

  std::cout
    << "---- simd" << '\n'
    << "<- r             = " << r << '\n'
    << "<- t             = " << t << '\n'
    << "-> polar(r, t)   = " << eve::polar(r, t) << '\n';

  std::cout
    << "---- scalar"  << '\n'
    << "-> polar(1, pi) = " << eve::polar(1.0, eve::pi(eve::as(1.0))) << '\n';
  return 0;
}
