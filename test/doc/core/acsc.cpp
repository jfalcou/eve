#include <eve/function/acsc.hpp>
#include <eve/wide.hpp>
#include <eve/constant/inf.hpp>
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<4>>;

int main()
{
  wide_ft pf = { 0.0f, 2.0f, -1.0f, -0.5f};

  std::cout
    << "---- simd" << '\n'
    << "<- pf =             " << pf << '\n'
    << "-> eve::acsc(pf) = " << eve::acsc(pf) << '\n';

  float xf = 1.0f;
  float yf = eve::Inf<float>();

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf =            " << xf << '\n'
    << "-> eve::acsc(xf)   " << eve::acsc(xf) << '\n'
    << "<- yf =            " << yf << '\n'
    << "-> eve::acsc(yf) = " << eve::acsc(yf) << '\n';
  return 0;
}
