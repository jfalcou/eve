#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;

consteval auto constexpr_is_nan(auto a) { return eve::is_nan(a); }

int main()
{
  wide_ft pf = {0.0f, 1.0f, -1.5f, 2.0f , eve::nan(eve::as<float>()),
                eve::inf(eve::as<float>()), eve::minf(eve::as<float>()),
                -eve::nan(eve::as<float>())};

  std::cout << "---- simd" << '\n'
            << "<- pf                         = " << pf << '\n'
            << "-> is_nan(pf)                 = " << eve::is_nan(pf) << '\n'
            << "-> is_nan[ignore_last(1)](pf) = " << eve::is_nan[eve::ignore_last(1)](pf) << '\n';

  float xf = 1.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf         = " << xf << '\n'
            << "-> is_nan(xf) = " << eve::is_nan(xf) << '\n';

  std::cout << "-> constexpr_is_nan(1.0f) = " << constexpr_is_nan(1.0f) << std::endl;

  return 0;
}
