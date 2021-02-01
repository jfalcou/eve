#include <eve/function/nbtrue.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;
using wide_it = eve::wide<std::int16_t, eve::fixed<4>>;

int main()
{
  wide_ft pf = {-1.0f, 0.0f, -3.0f, -0.0f};
  wide_it qf = {-1.0f, 2.0f, -3.0f, -32768.0f};

  std::cout << "---- simd" << '\n'
            << "<- pf         = " << pf << '\n'
            << "-> nbtrue(pf) = " << eve::nbtrue(pf) << '\n'
            << "<- qf         = " << qf << '\n'
            << "-> nbtrue(qf) = " << eve::nbtrue(qf) << '\n';

  float        xf = -0.0f;
  float        yf = -3.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf         = " << xf << '\n'
            << "-> nbtrue(xf) = " << eve::nbtrue(xf) << '\n'
            << "<- yf         = " << yf << '\n'
            << "-> nbtrue(yf) = " << eve::nbtrue(yf) << '\n';
  return 0;
}
