#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft pf = {0.0f, 1.0f, -1.0f, -2.0f};
  wide_ft qf = {1.0f, -1.0f, -1.0f, -2.0f};

  std::cout << "---- simd" << '\n'
            << "<- pf                                   = " << pf << '\n'
            << "<- qf                                   = " << qf << '\n'
            << "-> is_greater_equal(pf, qf)             = " << eve::is_greater_equal(pf, qf) << '\n'
            << "-> is_greater_equal[definitely2](pf, qf)= " << eve::is_greater_equal[eve::almost2](pf, qf) << '\n'
            << "-> is_greater_equal[ignore_all](pf, qf) = " << eve::is_greater_equal[eve::ignore_all](pf, qf) << '\n';

  float xf = 1.0f;
  float yf = 2.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf                       = " << xf << '\n'
            << "<- yf                       = " << yf << '\n'
            << "-> is_greater_equal(xf, yf) = " << eve::is_greater_equal(xf, yf) << '\n';
  return 0;
}
