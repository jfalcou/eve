#include <eve/module/combinatorial.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using w16_t = eve::wide<std::uint32_t, eve::fixed<8>>;
  w16_t pi16 = {52, 53, 6541, 6542, 0, 1, 999, 10000};

  std::cout << "---- simd" << '\n'
            << " <- pi16           = " << pi16 << '\n'
            << " -> uint32(nth_prime)(pi16)   = " << eve::uint32(eve::nth_prime)(pi16) << '\n'
            << " -> float32(nth_prime)(pi16)  = " << eve::float32(eve::nth_prime)(pi16) << '\n'
            << " -> float32(nth_prime(pi16))  = " << eve::float32(eve::nth_prime(pi16)) << "// mind the parentheses\n\n";

  std::uint16_t xi = 18;
  std::cout << "---- scalar" << '\n'
            << " xi                = " << xi << '\n'
            << " -> nth_prime(xi)  = " << eve::nth_prime(xi) << '\n';
  return 0;
}
