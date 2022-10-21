#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft pf = {0.0f, 1.0f, -1.0f,  eve::nan(as(-2.0f))};
  wide_ft qf = {1.0f, -1.0f, -1.0f, eve::nan(as(-2.0f))};

  std::cout << "---- simd" << '\n'
            << "<- pf                                 = " << pf << '\n'
            << "<- qf                                 = " << qf << '\n'
            << "-> eve::numeric(is_not_equal)(pf, qf) = " << eve::numeric(eve::is_not_equal)(pf, qf) << '\n';

  float xf = 1.0f;
  float yf = 2.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf                                 = " << xf << '\n'
            << "<- yf                                 = " << yf << '\n'
            << "-> eve::numeric(is_not_equal)(xf, yf) = " << eve::numeric(eve::is_not_equal)(xf, yf) << '\n';
  return 0;
}
