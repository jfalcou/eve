#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_it = eve::wide<std::uint32_t, eve::fixed<4>>;

consteval auto constexpr_bit_width(auto a) { return eve::bit_width(a); }

int main()
{
  wide_it pi = {14, 1, 3, 0};

  std::cout << "---- simd" << '\n'
            << "<- pi            = " << pi << '\n'
            << "-> bit_width(pi) = " << eve::bit_width(pi) << '\n';

  std::uint32_t xf = 48;

  std::cout << "---- scalar" << '\n'
            << "<- xf            = " << xf << '\n'
            << "-> bit_width(xf) = " << eve::bit_width(xf) << '\n';

  std::cout << "-> constexpr_bit_width(1) = " << constexpr_bit_width(1u) << std::endl;

  return 0;
}
