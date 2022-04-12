#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  float ep = eve::eps(eve::as<float>());
  wide_ft pf = {1.0f+ep, 0.5f*(1.0f+ep*4), -1.3f,   1.0f+4*ep};
  wide_ft qf = {1.0f-ep, 0.5f,             -1.3f,   1.0f-ep/2};
  wide_ft rf = {1.0f-ep, 0.5f,             -1.3f,   1.0f-ep/2};


  auto [a, b, c]  = eve::three_fma(pf, qf, rf);
  std::cout << "---- simd" << std::setprecision(8) << '\n'
            << "<- pf                     = " << pf << '\n'
            << "<- qf                     = " << qf << '\n'
            << "<- rf                     = " << qf << '\n'
            << "-> three_fma(pf, qf, rf)  = [" << '\n'
            << "                      " << a << ", \n"
            << "                      " << b << ", \n"
            << "                      " << c << '\n'
            << "                      ]\n";

  float xf = 0.5f*(1.0f+ep*4), yf = -1.3f, zf = -1.3f;
  auto [sa, sb, sc] =  eve::three_fma(xf, yf, zf);

  std::cout << "---- scalar" << '\n'
            << "<- xf                    =  " << xf << '\n'
            << "<- yf                    =  " << yf << '\n'
            << "<- zf                    =  " << zf << '\n'
            << "-> three_fma(xf, yf, zf) = [" << sa << ", " << sb << ", " << sc << "]\n"
            << "-> fma(double(xf), double(yf), double(zf) = " << fma(double(xf), double(yf), double(zf)) << '\n'
            << "-> double(sa)+double(sb)+double(sc)         " <<  double(sa)+double(sb)+double(sc)   << '\n';
  return 0;
}
