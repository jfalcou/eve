#include <eve/function/ellint_rc.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft pf = {1.0f, 0.0f, 1.5f, 3.0f};
  wide_ft qf = {1.0f, 4.0f, 0.2f, 0.5f};

  std::cout << "---- simd" << '\n'
            << "<- pf                = " << pf << '\n'
            << "<- qf                = " << qf << '\n'
            << "-> ellint_rc(pf, qf) = " << eve::ellint_rc(pf, qf) << '\n';

  float xf = 3.0f;
  float yf = 0.5f;

  std::cout << "---- scalar" << '\n'
            << "<- xf                = " << xf << '\n'
            << "<- yf                = " << yf << '\n'
            << "-> ellint_rc(xf, yf) = " << eve::ellint_rc(xf, yf) << '\n';

  return 0;
}
