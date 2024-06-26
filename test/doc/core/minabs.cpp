#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;

consteval auto constexpr_minabs(auto a, auto b) { return eve::minabs(a, b); }

int main()
{
  wide_ft pf = {0.0f, 1.0f,  1.0f, -2.0f, 2.0f,
                eve::inf(eve::as<float>()), eve::minf(eve::as<float>()), eve::nan(eve::as<float>())};
  wide_ft qf = {4.0f, 1.0f, -1.0f,  0.0f,  -3.0f,
                eve::nan(eve::as<float>()),  -eve::nan(eve::as<float>()), -2.0f};

  std::cout << "---- simd" << '\n'
            << "<- pf                        = " << pf << '\n'
            << "<- qf                        = " << qf << '\n'
            << "-> minabs(pf, qf)            = " << eve::minabs(pf, qf) << '\n'
            << "-> minabs[pedantic}(pf, qf)  = " << eve::minabs[eve::pedantic](pf, qf) << '\n'
            << "-> minabs[numeric](pf, qf)   = " << eve::minabs[eve::numeric](pf, qf) << '\n'
            << "-> minabs[pf <  0](pf, qf)   = " << eve::minabs[pf <  0](pf, qf) << '\n';

  float xf = -4.0f;
  float yf = 1.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf                        = " << xf << '\n'
            << "<- yf                        = " << yf << '\n'
            << "-> minabs(xf, yf)            = " << eve::minabs(xf, yf) << '\n';

  std::cout << "-> constexpr_minabs(1.0f,2.0f) = " << constexpr_minabs(1.0f,2.0f) << std::endl;

   return 0;
}
