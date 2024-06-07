#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_it = eve::wide<std::uint32_t, eve::fixed<8>>;

consteval auto constexpr_bit_floor(auto a) { return eve::bit_floor(a); }

int main()
{
  wide_it pi = {14, 1, 3, 7, 20, 23000, 0, 27};

  std::cout << "---- simd" << '\n'
            << "<- pi                    = " << pi << '\n'
            << "-> bit_floor(pi)         = " << eve::bit_floor(pi) << '\n'
            << "-> bit_floor[pi > 4](pi) = " << eve::bit_floor[pi > 4](pi) << '\n';

  std::uint32_t xf = 48;

  std::cout << "---- scalar" << '\n'
            << "<- xf            = " << xf << '\n'
            << "-> bit_floor(xf) = " << eve::bit_floor(xf) << '\n';

//  std::cout << "-> constexpr_bit_floor(1.0f) = " << constexpr_bit_floor(1u) << std::endl;

  return 0;
}
