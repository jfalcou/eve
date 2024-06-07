#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_it = eve::wide<std::uint32_t, eve::fixed<8>>;

consteval auto constexpr_firstbitset(auto a) { return eve::firstbitset(a); }

int main()
{
  wide_it pi = {14, 1, 3, 7, 20, 23000, 0, 27};

  std::cout << "---- simd" << '\n'
            << "<- pi                      = " << pi << '\n'
            << "-> firstbitset(pi)         = " << eve::firstbitset(pi) << '\n'
            << "-> firstbitset[pi > 4](pi) = " << eve::firstbitset[pi > 4](pi) << '\n';

  std::uint32_t xf = 48;

  std::cout << "---- scalar" << '\n'
            << "<- xf              = " << xf << '\n'
            << "-> firstbitset(xf) = " << eve::firstbitset(xf) << '\n';

  std::cout << "-> constexpr_firstbitset(1u) = " << constexpr_firstbitset(1u) << std::endl;

  return 0;
}
