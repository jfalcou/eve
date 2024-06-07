#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;

consteval auto constexpr_minmag(auto a, auto b) { return eve::minmag(a, b); }

int main()
{
  wide_ft pf = {0.0f, 1.0f,  1.0f, -2.0f, 2.0f,
                eve::inf(eve::as<float>()), eve::minf(eve::as<float>()), eve::nan(eve::as<float>())};
  wide_ft qf = {4.0f, 1.0f, -1.0f,  0.0f,  -3.0f,
                eve::nan(eve::as<float>()),  -eve::nan(eve::as<float>()), -2.0f};

  std::cout << "---- simd" << '\n'
            << "<- pf                        = " << pf << '\n'
            << "<- qf                        = " << qf << '\n'
            << "-> minmag(pf, qf)            = " << eve::minmag(pf, qf) << '\n'
            << "-> minmag[pedantic}(pf, qf)  = " << eve::minmag[eve::pedantic](pf, qf) << '\n'
            << "-> minmag[numeric](pf, qf)   = " << eve::minmag[eve::numeric](pf, qf) << '\n'
            << "-> minmag[pf <  0](pf, qf) = " << eve::minmag[pf <  0](pf, qf) << '\n';

  float xf = -4.0f;
  float yf = 1.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf                        = " << xf << '\n'
            << "<- yf                        = " << yf << '\n'
            << "-> minmag(xf, yf)            = " << eve::minmag(xf, yf) << '\n';

//  std::cout << "-> constexpr_minmag(1.0f,2.0f) = " << constexpr_minmag(1.0f,2.0f) << std::endl;

   return 0;
}
