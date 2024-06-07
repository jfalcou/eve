#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;
using wide_it = eve::wide<std::int16_t, eve::fixed<4>>;

consteval auto constexpr_none(auto a) { return eve::none(a); }

int main()
{
  wide_ft pf = {-0.0f, 0.0f, -0.0f, -0.0f};
  wide_it qi = {-1, 0, 30, -32768};

  std::cout << "---- simd" << '\n'
            << "<- pf                             = " << pf << '\n'
            << "-> none(pf != 0)                  = " << eve::none(pf != 0) << '\n'
            << "<- qi                             = " << qi << '\n'
            << "-> none(qi != 0)                  = " << eve::none(qi != 0) << '\n'
            << "-> none[ignore_first(1)](qi != 0) = " << eve::none[eve::ignore_first(1)](qi != 0) << '\n';

  float        xf = -0.0f;
  float        yf = -3.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf       = " << xf << '\n'
            << "-> none(xf) = " << eve::none(xf != 0) << '\n'
            << "<- yf       = " << yf << '\n'
            << "-> none(yf) = " << eve::none(yf != 0) << '\n';

//  std::cout << "-> constexpr_none(1.0f) = " << constexpr_none(1.0f) << std::endl;

  return 0;
}
