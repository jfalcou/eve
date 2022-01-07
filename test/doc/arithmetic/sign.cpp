#include <eve/function/sign.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;
using wide_it = eve::wide<std::int16_t, eve::fixed<4>>;

int main()
{
  wide_ft pf = {-0.0f, 2.0f, -3.0f, -32768.0f,
                 0.0f, -2.0f, 3.0f, 32768.0f};
  wide_it pi = { 0, 2, -3, -32768};

  std::cout << "---- simd" << '\n'
            << "<- pf       = " << pf << '\n'
            << "-> sign(pf) = " << eve::sign(pf) << '\n'
            << "<- pi       = " << pi << '\n'
            << "-> sign(pi) = " << eve::sign(pi) << '\n';

  float        xf = -327.68f;
  std::int16_t xi = -328;

  std::cout << "---- scalar" << '\n'
            << "<- xf       = " << xf << '\n'
            << "-> sign(xf) = " << eve::sign(xf) << '\n'
            << "<- xi       = " << xi << '\n'
            << "-> sign(xi) = " << eve::sign(xi) << '\n';
  return 0;
}
