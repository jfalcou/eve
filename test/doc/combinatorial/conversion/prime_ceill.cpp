#include <eve/module/combinatorial.hpp>
#include <eve/wide.hpp>

#include <iomanip>
#include <iostream>

int
main()
{
  using w32_t = eve::wide<std::uint32_t, eve::fixed<8>>;
  w32_t pi32  = {0, 6, 6542, 15, 104729, 104730, 10000, 1000};

  std::cout << "---- simd" << '\n'
            << " <- pi32                      = " << pi32 << '\n'
            << " -> float32(prime_ceil)(pi32) = " << eve::float32(eve::prime_ceil)(pi32)
            << "note nan meaning out of implemented range\n";
  return 0;
}
