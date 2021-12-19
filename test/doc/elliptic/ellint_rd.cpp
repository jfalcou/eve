//#include <eve/include/function/ellint_rd.hpp>
#include <eve/module/elliptic.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft pf = {1.0f, 0.0f, 1.5f, 3.0f};
  wide_ft qf = {1.0f, 4.0f, 0.2f, 0.5f};
  wide_ft rd = {2.0f, 1.0f, 0.1f, 0.4f};

  std::cout << "---- simd" << '\n'
            << "<- pf                    = " << pf << '\n'
            << "<- qf                    = " << qf << '\n'
            << "<- rd                    = " << rd << '\n'
            << "-> ellint_rd(pf, qf, rd) = " << eve::ellint_rd(pf, qf, rd) << '\n';

  float xf = 3.0f;
  float yf = 0.5f;
  float zf = 1.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf                    = " << xf << '\n'
            << "<- yf                    = " << yf << '\n'
            << "<- zf                    = " << zf << '\n'
            << "-> ellint_rd(xf, yf, zf) = " << eve::ellint_rd(xf, yf, zf) << '\n';

  return 0;
}
