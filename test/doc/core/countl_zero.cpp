#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_it = eve::wide<std::uint32_t, eve::fixed<4>>;

consteval auto constexpr_countl_zero(auto a) { return eve::countl_zero(a); }

int main()
{
  wide_it pi = {14, 1, 3, 0};

  std::cout << "---- simd" << '\n'
            << "<- pi              = " << pi << '\n'
            << "-> countl_zero(pi) = " << eve::countl_zero(pi) << '\n';

  std::uint32_t xf = 48;

  std::cout << "---- scalar" << '\n'
            << "<- xf              = " << xf << '\n'
            << "-> countl_zero(xf) = " << eve::countl_zero(xf) << '\n';

  std::cout << "-> constexpr_countl_zero(1.0f) = " << constexpr_countl_zero(1u) << std::endl;

  return 0;
}
