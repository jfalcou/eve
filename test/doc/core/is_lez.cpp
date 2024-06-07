#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

consteval auto constexpr_is_lez(auto a) { return eve::is_lez(a); }

int main()
{
  wide_ft pf = {0.0f, 1.0f, -1.0f, -0.0f};

  std::cout << "---- simd" << '\n'
            << "<- pf               = " << pf << '\n'
            << "-> is_lez(pf)       = " << eve::is_lez(pf) << '\n'
            << "-> is_lez[pf>0](pf) = " << eve::is_lez[pf>0](pf) << '\n';

  float xf = 1.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf         = " << xf << '\n'
            << "-> is_lez(xf) = " << eve::is_lez(xf) << '\n';

  std::cout << "-> constexpr_is_lez(1.0f) = " << constexpr_is_lez(1.0f) << std::endl;

  return 0;
}
