#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

consteval auto constexpr_is_gtz(auto a) { return eve::is_gtz(a); }

int main()
{
  wide_ft pf = {0.0f, 1.0f, -1.0f, -0.0f};

  std::cout << "---- simd" << '\n'
            << "<- pf                 = " << pf << '\n'
            << "-> is_gtz(pf)         = " << eve::is_gtz(pf) << '\n'
            << "-> is_gtz[pf > 0](pf) = " << eve::is_gtz[pf > 0](pf) << '\n';

  float xf = 1.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf         = " << xf << '\n'
            << "-> is_gtz(xf) = " << eve::is_gtz(xf) << '\n';

  std::cout << "-> constexpr_is_gtz(1.0f) = " << constexpr_is_gtz(1.0f) << std::endl;

  return 0;
}
