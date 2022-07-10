#include <eve/module/combinatorial.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using w32_t = eve::wide<std::int32_t, eve::fixed<4>>;
  w32_t pi32 = {93, 25, 32, 37}, qi32 = {42, 10, 27, 102};

  std::cout << "---- simd" << '\n'
            << " <- pi32                       = " << pi32 << '\n'
            << " <- qi32                       = " << qi32 << '\n'
            << " -> lcm(pi32, qi32)            = " << eve::lcm(pi32, qi32) << '\n';

  std::uint32_t xi = 18, yi = 60;

  std::cout << "---- scalar" << '\n'
            << " xi                 = " << xi << '\n'
            << " yi                 = " << yi << '\n'
            << " -> lcm(xi, yi)     = " << eve::lcm(xi, yi) << '\n';
  return 0;
}
