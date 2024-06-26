#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;

consteval auto constexpr_is_denormal(auto a) { return eve::is_denormal(a); }

int main()
{
  wide_ft pf = {0.0f,1.0f, -1.0f, -2.0f,
                eve::mindenormal(eve::as<float>()), eve::inf(eve::as<float>()),
                eve::minf(eve::as<float>()), eve::nan(eve::as<float>())};

  std::cout << "---- simd" << '\n'
            << "<- pf              = " << pf << '\n'
            << "-> is_denormal(pf) = " << eve::is_denormal(pf) << '\n'
            << "-> is_denormal[pf > 0](pf) = " << eve::is_denormal[pf > 0](pf) << '\n';
 
  float xf = 1.0f;
  float yf = eve::mindenormal(eve::as<float>());

  std::cout << "---- scalar" << '\n'
            << "<- xf              = " << xf << '\n'
            << "-> is_denormal(xf) = " << eve::is_denormal(xf) << '\n'
            << "<- yf              = " << yf << '\n'
            << "-> is_denormal(yf) = " << eve::is_denormal(yf) << '\n';

  std::cout << "-> constexpr_is_denormal(1.0f) = " << constexpr_is_denormal(1.0f) << std::endl;

  return 0;
}
