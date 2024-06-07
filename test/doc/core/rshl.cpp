#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using iT       = std::int32_t;
using uiT      = std::uint32_t;
using wide_it  = eve::wide<iT, eve::fixed<4>>;
using wide_uit = eve::wide<uiT, eve::fixed<4>>;

consteval auto constexpr_rshl(auto a, auto b) { return eve::rshl(a, b); }

int main()
{
  wide_uit pi = {100, 200, 2, 3};
  wide_it  qi = {1, -2, 3, -1};

  std::cout << "---- simd" << '\n'
            << "<- pi                     = " << pi << '\n'
            << "<- qi                     = " << qi << '\n'
            << "-> shl(pi, qi)            = " << eve::rshl(pi, qi) << '\n'
            << "-> rshl[pi!= 200](pi, qi) = " << eve::rshl[pi!= 200](pi, qi) << '\n';

  uiT xi = 2, yi = 3;

  std::cout << "---- scalar" << '\n'
            << "<- xi            = " << xi << '\n'
            << "<- yi            = " << yi << '\n'
            << "-> rshl(xi, yi)  = " << eve::rshl(xi, yi) << '\n';

  std::cout << "-> constexpr_rshl(1u,2u) = " << constexpr_rshl(1u,2u) << std::endl;

  return 0;
}
