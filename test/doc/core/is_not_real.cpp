#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

consteval auto constexpr_is_not_real(auto a) { return eve::is_not_real(a); }

int main()
{
  wide_ft pf = {0.0f, 1.0f, -0.0f, -2.0f};

  std::cout << "---- simd" << '\n'
            << "<- pf                      = " << pf << '\n'
            << "-> is_not_real(pf)         = " << eve::is_not_real(pf) << '\n'
            << "-> is_not_real[pf > 0](pf) = " << eve::is_not_real[pf > 0](pf) << '\n';

  float xf = 1.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf              = " << xf << '\n'
            << "-> is_not_real(xf) = " << eve::is_not_real(xf) << '\n';

  std::cout << "-> constexpr_is_not_real(1.0f) = " << constexpr_is_not_real(1.0f) << std::endl;

  return 0;
}
