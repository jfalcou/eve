#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;

consteval auto constexpr_mantissa(auto a) { return eve::mantissa(a); }

int main()
{
  wide_ft pf = {-1.0f, 0.0f, 367.0f, -1005600.0f, eve::mindenormal(eve::as<float>()),
               eve::inf(eve::as<float>()), eve::minf(eve::as<float>()), eve::nan(eve::as<float>())};

  std::cout << "---- simd" << '\n'
            << "<- pf           = " << pf << '\n'
            << "-> mantissa(pf) = " << eve::mantissa(pf) << '\n';

  float        xf = -32768.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf           = " << xf << '\n'
            << "-> mantissa(xf) = " << eve::mantissa(xf) << '\n';

//  std::cout << "-> constexpr_mantissa(1.0f) = " << constexpr_mantissa(1.0f) << std::endl;

  return 0;
}
