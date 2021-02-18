#include <eve/function/count_true.hpp>
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
            << "-> count_true(pf) = " << eve::count_true(pf) << '\n'
            << "<- qf         = " << qf << '\n'
            << "-> count_true(qf) = " << eve::count_true(qf) << '\n';

  float        xf = -0.0f;
  float        yf = -3.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf         = " << xf << '\n'
            << "-> count_true(xf) = " << eve::count_true(xf) << '\n'
            << "<- yf         = " << yf << '\n'
            << "-> count_true(yf) = " << eve::count_true(yf) << '\n';
  return 0;
}
