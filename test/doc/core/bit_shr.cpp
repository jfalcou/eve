#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using w_t = eve::wide<std::uint32_t, eve::fixed<4>>;
  w_t pi = {3, 602, 3, 4001}, qi = {4, 1, 2, 0};
  std::uint32_t z = 5;
  std::cout << "---- simd" << '\n'
            << " <- pi              = " << pi << '\n'
            << " <- qi              = " << qi << '\n'
            << " <- z               = " << z  << '\n'
            << " -> bit_shr(pi, qi) = " << eve::bit_shr(pi, qi) << '\n'
            << " -> bit_shr(z,  qi) = " << eve::bit_shr(z,  qi) << '\n'
            << " -> bit_shr(pi, z ) = " << eve::bit_shr(pi, z) << '\n';

  std::uint32_t a = 1;
  std::uint32_t n = 4;

  std::cout << "---- scalar" << '\n'
            << " <- a             = " << a << '\n'
            << " <- n             = " << n << '\n'
            << " -> bit_shr(a, n) = " << eve::bit_shr(a, n) << '\n';
  return 0;
}
