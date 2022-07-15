#include <eve/module/combinatorial.hpp>
#include <eve/wide.hpp>

#include <iostream>

int
main()
{
  using w_t = eve::wide<std::int8_t, eve::fixed<4>>;
  w_t pi8 = {93, 25, 32, 37}, qi8 = {42, 10, 27, 102};

  std::cout << "---- simd" << '\n'
            << " <- pi8                        = " << pi8 << '\n'
            << " <- qi8                        = " << qi8 << '\n'
            << " -> lcm(pi8, qi8)              = " << eve::lcm(pi8, qi8)
            << "// incorrect due to overflow\n"
            << " -> upgrade_(lcm)(pi8, qi8))    = " << eve::upgrade_(eve::lcm)(pi8, qi8) << '\n';

  return 0;
}
