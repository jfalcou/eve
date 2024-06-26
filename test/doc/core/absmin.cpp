#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using eve::saturated;
using eve::numeric;
using eve::pedantic;
using eve::wide;
using eve::as;
using std::int32_t;

using wide_ft = eve::wide<float, eve::fixed<8>>;

consteval auto constexpr_absmin(auto a, auto b) { return eve::absmin(a, b); }

int main()
{
  wide_ft pf = {0.0f, 1.0f,  1.0f, -2.0f, 2.0f,
                eve::inf(eve::as<float>()), eve::minf(eve::as<float>()), eve::nan(eve::as<float>())};
  wide_ft qf = {4.0f, 1.0f, -1.0f,  0.0f,  -3.0f,
                eve::nan(eve::as<float>()),  -eve::nan(eve::as<float>()), -2.0f};

  std::cout << "---- simd" << '\n'
            << "<- pf                        = " << pf << '\n'
            << "<- qf                        = " << qf << '\n'
            << "-> absmin(pf, qf)            = " << eve::absmin(pf, qf) << '\n'
            << "-> absmin[pedantic](pf, qf)  = " << eve::absmin[eve::pedantic](pf, qf) << '\n'
            << "-> absmin[numeric](pf, qf)   = " << eve::absmin[eve::numeric](pf, qf) << '\n';

  float xf = -4.0f;
  float yf = 1.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf                        = " << xf << '\n'
            << "<- yf                        = " << yf << '\n'
            << "-> absmin(xf, yf)            = " << eve::absmin(xf, yf) << '\n'
            << "-> absmin[pedantic](xf, yf)  = " << eve::absmin[eve::pedantic](xf, yf) << '\n'
            << "-> absmin[numeric](xf, yf)   = " << eve::absmin[eve::numeric](xf, yf) << '\n';

  std::cout << "-> constexpr_absmin(1.0f,2.0f)        = " << constexpr_absmin(1.0f,2.0f) << std::endl;

   return 0;
}
