#include <eve/module/combinatorial.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

int main()
{
  using w32_t = eve::wide<std::uint32_t, eve::fixed<8>>;
  w32_t pi32 = {2, 6, 6542, 15, 1, 200000, 10000, 1000};

  std::cout << "---- simd" << '\n'
            << " <- pi32              = " << pi32 << '\n'
            << " -> float32(prime_floor)(pi32) = " << eve::float32(eve::prime_floor)(pi32) << " // note -nan meaning out of implemented range\n";
  return 0;
}
