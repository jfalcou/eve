#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_it = eve::wide<std::uint32_t, eve::fixed<8>>;

consteval auto constexpr_bit_ceil(auto a) { return eve::bit_ceil(a); }

int main()
{
  wide_it pi = {14, 1, 3, 7, 20, 23000, 0, 27};

  std::cout << "---- simd" << '\n'
            << "<- pi                   = " << pi << '\n'
            << "-> bit_ceil[pi > 4](pi) = " << eve::bit_ceil[pi > 4](pi) << '\n'
            << "-> bit_ceil(pi)         = " << eve::bit_ceil(pi) << '\n';

  std::uint32_t xf = 48;

  std::cout << "---- scalar" << '\n'
            << "<- xf           = " << xf << '\n'
            << "-> bit_ceil(xf) = " << eve::bit_ceil(xf) << '\n';

  std::cout << "-> constexpr_bit_ceil(1.0f) = " << constexpr_bit_ceil(1.0f) << std::endl;

  return 0;
}
