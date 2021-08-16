#include <eve/function/all.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;
using wide_it = eve::wide<std::int16_t, eve::fixed<4>>;

int main()
{
  wide_ft pf = {-1.0f, 0.0f, -3.0f, -32768.0f};
  wide_it qi = {-1.0f, 2.0f, -3.0f, -32768.0f};

  std::cout << "---- simd" << '\n'
            << "<- pf       = " << pf << '\n'
            << "-> all(pf)  = " << eve::all(pf) << '\n'
            << "<- qi       = " << qi << '\n'
            << "-> all(qi)  = " << eve::all(qi) << '\n';

  float        xf = -0.0f;
  float        yf = -3.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf      = " << xf << '\n'
            << "-> all(xf) = " << eve::all(xf) << '\n'
            << "<- yf      = " << yf << '\n'
            << "-> all(yf) = " << eve::all(yf) << '\n';
  return 0;
}
