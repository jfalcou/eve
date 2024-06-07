#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_it = eve::wide<std::uint32_t, eve::fixed<4>>;

consteval auto constexpr_popcount(auto a) { return eve::popcount(a); }

int main()
{
  wide_it pi = {14, 1, 3, 0};

  std::cout << "---- simd" << '\n'
            << "<- pi           = " << pi << '\n'
            << "-> popcount(pi) = " << eve::popcount(pi) << '\n';

  std::uint32_t xf = 48;

  std::cout << "---- scalar" << '\n'
            << "<- xf           = " << xf << '\n'
            << "-> popcount(xf) = " << eve::popcount(xf) << '\n';

  std::cout << "-> constexpr_popcount(1u) = " << constexpr_popcount(1u) << std::endl;

  return 0;
}
