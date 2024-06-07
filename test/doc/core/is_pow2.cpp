#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_it = eve::wide<std::uint32_t, eve::fixed<8>>;

consteval auto constexpr_is_pow2(auto a) { return eve::is_pow2(a); }

int main()
{
  wide_it pi = {14, 1, 3, 0, 16, 23000, 0, 27};

  std::cout << "---- simd" << '\n'
            << "<- pi                   = " << pi << '\n'
            << "-> is_pow2(pi)          = " << eve::is_pow2(pi) << '\n'
            << "-> is_pow2[pi < 10](pi) = " << eve::is_pow2[pi < 10](pi) << '\n';

  std::uint32_t xf = 48;

  std::cout << "---- scalar" << '\n'
            << "<- xf          = " << xf << '\n'
            << "-> is_pow2(xf) = " << eve::is_pow2(xf) << '\n';

  std::cout << "-> constexpr_is_pow2(4) = " << constexpr_is_pow2(4) << std::endl;

  return 0;
}
