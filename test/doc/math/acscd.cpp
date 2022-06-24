#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<4>>;

int main()
{
  wide_ft pf = { 0.0f, 2.0f, -1.0f, -0.5f};

  std::cout
    << "---- simd" << '\n'
    << "<- pf        = " << pf << '\n'
    << "-> acscd(pf) = " << eve::acscd(pf) << '\n'
    ;

  float xf = 1.0f;
  float yf = eve::inf(eve::as<float>());

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf        = " << xf << '\n'
    << "-> acscd(xf) = " << eve::acscd(xf) << '\n'
    << "<- yf        = " << yf << '\n'
    << "-> acscd(yf) = " << eve::acscd(yf) << '\n';
  return 0;
}
