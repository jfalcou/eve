#include <eve/function/predicates.hpp>
#include <eve/wide.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/mindenormal.hpp>
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<4>>;

int main()
{
  wide_ft pf = { 0.0f, 1.0f, -1.0f, -2.0f};

  std::cout
    << "---- simd" << '\n'
    << "<- pf =                  " << pf << '\n'
    << "-> eve::is_even(pf) = " << eve::is_even(pf) << '\n';

  float xf = 1.0f;
  float yf = 2.0f;

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf =                  " << xf << '\n'
    << "-> eve::is_even(xf) = " << eve::is_even(xf) << '\n'
    << "<- yf =                  " << yf << '\n'
    << "-> eve::is_even(yf) = " << eve::is_even(yf) << '\n';
  return 0;
}
