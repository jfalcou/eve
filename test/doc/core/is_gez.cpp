#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

consteval auto constexpr_is_gez(auto a) { return eve::is_gez(a); }

int main()
{
  wide_ft pf = {0.0f, 1.0f, -1.0f, -0.0f};

  std::cout << "---- simd" << '\n'
            << "<- pf               = " << pf << '\n'
            << "-> is_gez(pf)       = " << eve::is_gez(pf) << '\n'
            << "-> is_gez[pf>0](pf) = " << eve::is_gez[pf>0](pf) << '\n';

  float xf = 1.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf         = " << xf << '\n'
            << "-> is_gez(xf) = " << eve::is_gez(xf) << '\n';

  std::cout << "-> constexpr_is_gez(1.0f) = " << constexpr_is_gez(1.0f) << std::endl;

  return 0;
}
