#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using iT       = std::int32_t;
using uiT      = std::uint32_t;
using wide_it  = eve::wide<iT, eve::fixed<4>>;
using wide_uit = eve::wide<uiT, eve::fixed<4>>;

consteval auto constexpr_rshr(auto a, auto b) { return eve::rshr(a, b); }

int main()
{
  wide_uit pi = {100, 200, 2, 3};
  wide_it qi  = {1, -2, 3, -1};

  std::cout << "---- simd" << '\n'
            << "<- pi                     = " << pi << '\n'
            << "<- qi                     = " << qi << '\n'
            << "-> shl(pi, qi)            = " << eve::rshr(pi, qi) << '\n'
            << "-> rshr[pi!= 200](pi, qi) = " << eve::rshr[pi!= 200](pi, qi) << '\n';

  uiT xi = 2, yi = 3;

  std::cout << "---- scalar" << '\n'
            << "<- xi            = " << xi << '\n'
            << "<- yi            = " << yi << '\n'
            << "-> rshr(xi, yi)  = " << eve::rshr(xi, yi) << '\n';

  std::cout << "-> constexpr_rshr(1u,2u) = " << constexpr_rshr(1u,2u) << std::endl;

  return 0;
}
