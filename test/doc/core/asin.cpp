#include <eve/function/asin.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<4>>;

int main()
{
  wide_ft pf = { 0.0f, 1.0f, -1.0f, -0.5f};

  std::cout
    << "---- simd" << '\n'
    << "<- pf =            " << pf << '\n'
    << "-> eve::asin(pf) = " << eve::asin(pf) << '\n';

  float xf = 1.0f;
  float yf = eve::Nan<float>();

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf =            " << xf << '\n'
    << "-> eve::asin(xf) = " << eve::asin(xf) << '\n'
    << "<- yf =            " << yf << '\n'
    << "-> eve::asin(yf) = " << eve::asin(yf) << '\n';
  return 0;
}
