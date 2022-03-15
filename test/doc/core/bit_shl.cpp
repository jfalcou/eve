
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using w_t = eve::wide<std::uint32_t, eve::fixed<4>>;
  w_t pi = {3, 2, 3, 4}, qi = {4, 1, 2, 0};
  std::uint32_t z = 5;
  std::cout << "---- simd" << '\n'
            << " <- pi              = " << pi << '\n'
            << " <- qi              = " << qi << '\n'
            << " <- z               = " << z  << '\n'
            << " -> bit_shl(pi, qi) = " << eve::bit_shl(pi, qi) << '\n'
            << " -> bit_shl(z,  qi) = " << eve::bit_shl(z,  qi) << '\n'
            << " -> bit_shl(pi, z ) = " << eve::bit_shl(pi, z) << '\n';

  std::uint32_t a = 1;
  std::uint32_t n = 4;

  std::cout << "---- scalar" << '\n'
            << " <- a             = " << a << '\n'
            << " <- n             = " << n << '\n'
            << " -> bit_shl(a, n) = " << eve::bit_shl(a, n) << '\n';
  return 0;
}
