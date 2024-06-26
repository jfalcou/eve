#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;

consteval auto constexpr_negabsmin(auto a, auto b) { return eve::negabsmin(a, b); }

int main()
{
  wide_ft pf = {0.0f, 1.0f,  1.0f, -2.0f, 2.0f,
                eve::inf(eve::as<float>()), eve::minf(eve::as<float>()), eve::nan(eve::as<float>())};
  wide_ft qf = {4.0f, 1.0f, -1.0f,  0.0f,  -3.0f,
                eve::nan(eve::as<float>()),  -eve::nan(eve::as<float>()), -2.0f};

  std::cout << "---- simd" << '\n'
            << "<- pf                             = " << pf << '\n'
            << "<- qf                             = " << qf << '\n'
            << "-> negabsmin(pf, qf)              = " << eve::negabsmin(pf, qf) << '\n'
            << "-> negabsmin[pedantic](pf, qf)    = " << eve::negabsmin[eve::pedantic](pf, qf) << '\n'
            << "-> negabsmin[numeric](pf, qf)     = " << eve::negabsmin[eve::numeric](pf, qf) << '\n'
            << "-> negabsmin[pf <  -1.0f](pf, qf) = " << eve::negabsmin[pf < -1.0f](pf, qf) << '\n';

  float xf = -4.0f;
  float yf = 1.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf                        = " << xf << '\n'
            << "<- yf                        = " << yf << '\n'
            << "-> negabsmin(xf, yf)           = " << eve::negabsmin(xf, yf) << '\n'
            << "-> negabsmin[pedantic](xf, yf) = " << eve::negabsmin[eve::pedantic](xf, yf) << '\n'
            << "-> negabsmin[numeric](xf, yf)  = " << eve::negabsmin[eve::numeric](xf, yf) << '\n';


  std::cout << "-> constexpr_negabsmin(1.0f,2.0f) = " << constexpr_negabsmin(1.0f,2.0f) << std::endl;

   return 0;
}
