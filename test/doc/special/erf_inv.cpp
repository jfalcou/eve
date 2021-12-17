//#include <eve/function/erf_inv.hpp>
#include <eve/module/special.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<4>>;

int main()
{
  wide_ft pf = { 0.0f, 1.0f, -1.0f, -0.5f};

  std::cout
    << "---- simd" << '\n'
    << "<- pf            = " << pf << '\n'
    << "-> eve::erf_inv(pf) = " << eve::erf_inv(pf) << '\n';

  float xf = 1.0f;
  float yf = 2.0f;

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf            = " << xf << '\n'
    << "-> eve::erf_inv(xf) = " << eve::erf_inv(xf) << '\n'
    << "<- yf            = " << yf << '\n'
    << "-> eve::erf_inv(yf) = " << eve::erf_inv(yf) << '\n';
  return 0;
}
