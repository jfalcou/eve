#include <eve/function/ellint_rj.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<double, eve::fixed<4>>;

int main()
{
//   wide_ft pf = {1.0f, 0.0f, 1.5f, 3.0f};
//   wide_ft qf = {1.0f, 4.0f, 0.2f, 0.5f};
//   wide_ft rf = {2.0f, 1.0f, 0.1f, 0.4f};
//   wide_ft sf = {2.2f, 0.5f, 0.3f, 2.4f};

  wide_ft pf = {0.0f, 0.0f, 0.0f, 3.0f};
  wide_ft qf = {0.19f, 4.0f, 0.4375f, 0.5f};
  wide_ft rf = {1.0f, 1.0f, 1.0f, 1.0f};
  wide_ft sf = {0.19f, 0.5f, 0.87071f, 2.4f};
  std::cout << "---- simd" << '\n'
            << "<- pf                        = " << pf << '\n'
            << "<- qf                        = " << qf << '\n'
            << "<- rf                        = " << rf << '\n'
            << "<- sf                        = " << sf << '\n'
            << "-> ellint_rj(pf, qf, rf, sf) = " << eve::ellint_rj(pf, qf, rf, sf) << '\n';

  float xf = 3.0f;
  float yf = 0.5f;
  float zf = 1.0f;
  float uf = -3.4f;

  std::cout << "---- scalar" << '\n'
            << "<- xf                        = " << xf << '\n'
            << "<- yf                        = " << yf << '\n'
            << "<- zf                        = " << zf << '\n'
            << "<- uf                        = " << uf << '\n'
            << "-> ellint_rj(xf, yf, zf, uf) = " << eve::ellint_rj(xf, yf, zf, uf) << '\n';

  return 0;
}
