#include <eve/function/lcm.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using w_t = eve::wide<std::int8_t, eve::fixed<4>>;
  w_t pi8 = {93, -25, 32, 37}, qi8 = {42, 10, 27, 102};
  using w32_t = eve::wide<std::int32_t, eve::fixed<4>>;
  w32_t pi32 = {93, -25, 32, 37}, qi32 = {42, 10, 27, 102};

  std::cout << "---- simd" << '\n'
            << " <- pi8                        = " << pi8 << '\n'
            << " <- qi8                        = " << qi8 << '\n'
            << " -> lcm(pi8, qi8)              = " << eve::lcm(pi8, qi8) << '\n'
            << " -> upgrade_(lcm)(pi8, qi8))   = " << eve::upgrade_(eve::lcm)(pi8, qi8) << '\n'
            << " -> lcm(pi32, qi32)            = " << eve::lcm(pi32, qi32) << '\n';

  std::uint32_t xi = 18, yi = 60;

  std::cout << "---- scalar" << '\n'
            << " xi                 = " << xi << '\n'
            << " yi                 = " << yi << '\n'
            << " -> lcm(xi, yi)     = " << eve::lcm(xi, yi) << '\n';
  return 0;
}
