#include <eve/function/primes.hpp>
#include <eve/wide.hpp>
#include <iomanip>

int main()
{
  using w16_t = eve::wide<std::uint16_t, eve::fixed<8>>;
  w16_t pi16 = {53, 54, 6542, 6543, 1, 9999, 10000, 10001};

  std::cout << "---- simd" << '\n'
            << " <- pi16           = " << pi16 << '\n'
            << " -> primes(pi16)   = " << eve::primes(pi16) << '\n'
            << " -> uint32(primes)(pi16)   = " << eve::uint32(eve::primes)(pi16) << '\n'
            << " -> float32(primes)(pi16)  = " << eve::float32(eve::primes)(pi16) << '\n'
            << " -> float32(primes(pi16))  = " << eve::float32(eve::primes(pi16)) << "// mind the parentheses\n\n";

  std::uint16_t xi = 18;
  std::cout << "---- scalar" << '\n'
            << " xi                = " << xi << '\n'
            << " -> primes(xi)     = " << eve::primes(xi) << '\n';
  return 0;
}
