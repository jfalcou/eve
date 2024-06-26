#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

consteval auto constexpr_is_ltz(auto a) { return eve::is_ltz(a); }

int main()
{
  wide_ft pf = {0.0f, 1.0f, -1.0f, -0.0f};

  std::cout << "---- simd" << '\n'
            << "<- pf               = " << pf << '\n'
            << "-> is_ltz(pf)       = " << eve::is_ltz(pf) << '\n'
            << "-> is_ltz[pf>0](pf) = " << eve::is_ltz[pf>0](pf) << '\n';


  float xf = 1.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf         = " << xf << '\n'
            << "-> is_ltz(xf) = " << eve::is_ltz(xf) << '\n';

  std::cout << "-> constexpr_is_ltz(1.0f) = " << constexpr_is_ltz(1.0f) << std::endl;

  return 0;
}
