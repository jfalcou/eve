//#include <eve/function/asecd.hpp>
#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <eve/constant/inf.hpp>
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<4>>;

int main()
{
  wide_ft pf = { 0.0f, 2.0f, -1.0f, -0.5f};

  std::cout
    << "---- simd" << '\n'
    << "<- pf             = " << pf << '\n'
    << "-> eve::asecd(pf) = " << eve::asecd(pf) << '\n';

  float xf = 1.0f;
  float yf = eve::inf(eve::as<float>());

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf             = " << xf << '\n'
    << "-> eve::asecd(xf) = " << eve::asecd(xf) << '\n'
    << "<- yf             = " << yf << '\n'
    << "-> eve::asecd(yf) = " << eve::asecd(yf) << '\n';
  return 0;
}
