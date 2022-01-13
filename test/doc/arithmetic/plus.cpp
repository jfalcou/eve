//#include <eve/function/plus.hpp>
#include <eve/module/arithmetic.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;
using wide_it = eve::wide<std::int16_t, eve::fixed<4>>;

int main()
{
  wide_ft pf = {-1.0f, 2.0f, -3.0f, -32768.0f};
  wide_it pi = {-1, 2, -3, -32768};

  std::cout << "---- simd" << '\n'
            << "<- pf       = " << pf << '\n'
            << "-> plus(pf) = " << eve::plus(pf) << '\n'
            << "<- pi       = " << pi << '\n'
            << "-> plus(pi) = " << eve::plus(pi) << '\n';

  float        xf = -32768.0f;
  std::int16_t xi = -32768;

  std::cout << "---- scalar" << '\n'
            << "<- xf       = " << xf << '\n'
            << "-> plus(xf) = " << eve::plus(xf) << '\n'
            << "<- xi       = " << xi << '\n'
            << "-> plus(xi) = " << eve::plus(xi) << '\n';
  return 0;
}
