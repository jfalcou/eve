#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_it = eve::wide<std::uint32_t, eve::fixed<4>>;

consteval auto constexpr_countr_one(auto a) { return eve::countr_one(a); }

int main()
{
  wide_it pi = {14, 1, 3, 0};

  std::cout << "---- simd" << '\n'
            << "<- pi             = " << pi << '\n'
            << "-> countr_one(pi) = " << eve::countr_one(pi) << '\n';

  std::uint32_t xf = 48;

  std::cout << "---- scalar" << '\n'
            << "<- xf             = " << xf << '\n'
            << "-> countr_one(xf) = " << eve::countr_one(xf) << '\n';

  std::cout << "-> constexpr_countr_one(1.0f) = " << constexpr_countr_one(1u) << std::endl;

  return 0;
}
