#include <eve/module/combinatorial.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using w16_t = eve::wide<std::uint16_t, eve::fixed<8>>;
  w16_t pi16 = {52, 53, 6541, 6542, 0, 1, 999, 10000};

  std::cout << "---- simd" << '\n'
            << " <- pi16              = " << pi16 << '\n'
            << " -> nth_prime(pi16)   = " << eve::nth_prime(pi16) << " // note the 0 outputs meaning overflow or out of range\n";

  std::uint16_t xi = 18;
  std::cout << "---- scalar" << '\n'
            << " xi                   = " << xi << '\n'
            << " -> nth_prime(xi)     = " << eve::nth_prime(xi) << '\n';
  return 0;
}
