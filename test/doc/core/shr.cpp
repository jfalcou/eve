#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using iT      = std::int32_t;
using wide_it = eve::wide<iT, eve::fixed<4>>;

consteval auto constexpr_shr(auto a, auto b) { return eve::shr(a, b); }

int main()
{
  wide_it pi = {100, 200, -2, 3};
  wide_it qi = {1, 2, 3, 2};

  std::cout << "---- simd" << '\n'
            << "<- pi                    = " << pi << '\n'
            << "<- qi                    = " << qi << '\n'
            << "-> eve::shr(pi, qi)      = " << eve::shr(pi, qi) << '\n'
            << "-> shr[pi!= 200](pi, qi) = " << eve::shr[pi!= 200](pi, qi) << '\n';

  iT xi = 2, mxi = -2, yi = 3;

  std::cout << "---- scalar" << '\n'
            << "<- xi                = " << xi << '\n'
            << "<- mxi               = " << mxi << '\n'
            << "<- yi                = " << yi << '\n'
            << "-> eve::shr(xi, yi)  = " << eve::shr(xi, yi) << '\n'
            << "-> eve::shr(mxi, yi) = " << eve::shr(mxi, yi) << '\n';

  std::cout << "-> constexpr_shr(1u,2u) = " << constexpr_shr(1u,2u) << std::endl;

  return 0;
}
