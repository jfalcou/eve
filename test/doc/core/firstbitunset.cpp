#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_it = eve::wide<std::uint32_t, eve::fixed<8>>;

consteval auto constexpr_firstbitunset(auto a) { return eve::firstbitunset(a); }

int main()
{
  wide_it pi = {14, 1, 3, 7, 20, 23000, 0, 27};

  std::cout << "---- simd" << '\n'
            << "<- pi                        = " << pi << '\n'
            << "-> firstbitunset(pi        ) = " << eve::firstbitunset(pi) << '\n'
            << "-> firstbitunset[pi > 4](pi) = " << eve::firstbitunset[pi > 4](pi) << '\n';

  std::uint32_t xf = 48;

  std::cout << "---- scalar" << '\n'
            << "<- xf                = " << xf << '\n'
            << "-> firstbitunset(xf) = " << eve::firstbitunset(xf) << '\n';

  std::cout << "-> constexpr_firstbitunset(1u) = " << constexpr_firstbitunset(1u) << std::endl;

  return 0;
}
