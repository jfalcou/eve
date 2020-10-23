#include <eve/function/erfc_inv.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<4>>;

int main()
{
  wide_ft pf = { 0.0f, 1.0f, 1.5f, 1.75f};

  std::cout
    << "---- simd" << '\n'
    << "<- pf            = " << pf << '\n'
    << "-> eve::erfc_inv(pf) = " << eve::erfc_inv(pf) << '\n';

  float xf = 1.0f;
  float yf = 2.0f;

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf            = " << xf << '\n'
    << "-> eve::erfc_inv(xf) = " << eve::erfc_inv(xf) << '\n'
    << "<- yf            = " << yf << '\n'
    << "-> eve::erfc_inv(yf) = " << eve::erfc_inv(yf) << '\n';
  return 0;
}
