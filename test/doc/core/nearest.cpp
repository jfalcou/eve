#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;

consteval auto constexpr_nearest(auto a) { return eve::nearest(a); }

int main()
{
  wide_ft pf = {-1.0f, -1.3f, -1.5f, -1.7f, 2.0f, 2.3f, 2.5f, 2.7f};

  std::cout << "---- simd" << '\n'
            << "<- pf                   = " << pf << '\n'
            << "-> nearest(pf)          = " << eve::nearest(pf) << '\n'
            << "-> nearest[pf > -1](pf) = " << eve::nearest[pf > -1](pf) << '\n';

  float xf = -32.768f;

  std::cout << "---- scalar" << '\n'
            << "<- xf          = " << xf << '\n'
            << "-> nearest(xf) = " << eve::nearest(xf) << '\n';

  std::cout << "-> constexpr_nearest(1.0f) = " << constexpr_nearest(1.0f) << std::endl;

  return 0;
}
