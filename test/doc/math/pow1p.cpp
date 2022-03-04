#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{
  wide_ft pf = {2.0f, 3.0f, -4.0f, 2.0f, 2.0f,
                eve::inf(eve::as<float>()), eve::minf(eve::as<float>()), eve::nan(eve::as<float>())};
  wide_ft qf = {4.0f, 1.0f, -1.0f,  0.5f,  0.0f,
                -2.0f, -3.0f,  2.5f};

  std::cout << "---- simd" << '\n'
            << "<- pf                      = " << pf << '\n'
            << "<- qf                      = " << qf << '\n'
            << "-> pow1p(pf, qf)           = " << eve::pow1p(pf, qf) << '\n'
            << "-> diff_1st(pow1p)(pf, qf) = " << eve::diff_1st(eve::pow1p)(pf, qf) << '\n'
            << "-> diff_2nd(pow1p)(pf, qf) = " << eve::diff_2nd(eve::pow1p)(pf, qf) << '\n';

  float xf = 4.0f;
  float yf = -1.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf            = " << xf << '\n'
            << "<- yf            = " << yf << '\n'
            << "-> pow1p(xf, yf) = " << eve::pow1p(xf, yf) << '\n';
  return 0;
}
