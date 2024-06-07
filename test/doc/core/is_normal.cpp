#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;

consteval auto constexpr_is_normal(auto a) { return eve::is_normal(a); }

int main()
{
  wide_ft pf = {0.0f,1.0f, -1.0f, -2.0f,
                eve::mindenormal(eve::as<float>()), eve::inf(eve::as<float>()),
                eve::minf(eve::as<float>()), eve::nan(eve::as<float>())};

  std::cout << "---- simd" << '\n'
            << "<- pf                  = " << pf << '\n'
            << "-> is_normal(pf)       = " << eve::is_normal(pf) << '\n'
            << "-> is_normal[pf>0](pf) = " << eve::is_normal[pf > 0](pf) << '\n';

  float xf = 1.0f;
  float yf = eve::mindenormal(eve::as<float>());

  std::cout << "---- scalar" << '\n'
            << "<- xf            = " << xf << '\n'
            << "-> is_normal(xf) = " << eve::is_normal(xf) << '\n'
            << "<- yf            = " << yf << '\n'
            << "-> is_normal(yf) = " << eve::is_normal(yf) << '\n';

  std::cout << "-> constexpr_is_normal(1.0f) = " << constexpr_is_normal(1.0f) << std::endl;

  return 0;
}
