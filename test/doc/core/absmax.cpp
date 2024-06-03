#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;

consteval auto constexpr_absmax(auto a, auto b) { return eve::absmax(a, b); }

int main()
{
  wide_ft pf = {0.0f, 1.0f,  1.0f, -2.0f, 2.0f,
                eve::inf(eve::as<float>()), eve::minf(eve::as<float>()), eve::nan(eve::as<float>())};
  wide_ft qf = {4.0f, 1.0f, -1.0f,  0.0f,  -3.0f,
                eve::nan(eve::as<float>()),  -eve::nan(eve::as<float>()), -2.0f};

  std::cout << "---- simd" << '\n'
            << "<- pf                        = " << pf << '\n'
            << "<- qf                        = " << qf << '\n'
            << "-> absmax(pf, qf)            = " << eve::absmax(pf, qf) << '\n'
            << "-> absmax[pedantic](pf, qf)  = " << eve::absmax[eve::pedantic](pf, qf) << '\n'
            << "-> absmax[numeric](pf, qf)   = " << eve::absmax[eve::numeric](pf, qf) << '\n';

  float xf = -4.0f;
  float yf = 1.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf                        = " << xf << '\n'
            << "<- yf                        = " << yf << '\n'
            << "-> absmax(xf, yf)            = " << eve::absmax(xf, yf) << '\n'
            << "-> absmax[pedantic](xf, yf)  = " << eve::absmax[eve::pedantic](xf, yf) << '\n'
            << "-> absmax[numeric](xf, yf)   = " << eve::absmax[eve::numeric](xf, yf) << '\n';

  std::cout << "-> constexpr_absmax(1.0f,2.0f)        = " << constexpr_absmax(1.0f,2.0f) << std::endl;

   return 0;
}
