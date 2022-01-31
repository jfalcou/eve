//#include <eve/function/is_not_less.hpp>
#include <eve/module/arithmetic.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft pf = {0.0f, 1.0f, -1.0f, -2.0f};
  wide_ft qf = {1.0f, -1.0f, 0.0f, -2.0f};

  std::cout << "---- simd" << '\n'
            << "<- pf                  = " << pf << '\n'
            << "<- qf                  = " << qf << '\n'
            << "-> is_not_less(pf, qf) = " << eve::is_not_less(pf, qf) << '\n';

  float xf = 1.0f;
  float yf = 2.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf                  = " << xf << '\n'
            << "<- yf                  = " << yf << '\n'
            << "-> is_not_less(xf, yf) = " << eve::is_not_less(xf, yf) << '\n';
  return 0;
}
