#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using w_t = eve::wide<std::uint32_t, eve::fixed<4>>;
  w_t pi = {3, 2, 3, 4}, qi = {4, 1, 1, ~0};
  std::uint32_t z = 5;
  std::cout << "---- simd" << '\n'
            << " <- pi                 = " << pi << '\n'
            << " <- qi                 = " << qi << '\n'
            << " <- z                  = " << z  << '\n'
            << " -> bit_notand(pi, qi) = " << eve::bit_notand(pi, qi) << '\n'
            << " -> bit_notand(z,  qi) = " << eve::bit_notand(z,  qi) << '\n'
            << " -> bit_notand(pi, z ) = " << eve::bit_notand(pi, z) << '\n';

  std::uint32_t mask = 1 >> 31;
  float xi = -3.4565;

  std::cout << "---- scalar" << '\n'
            << " <- xi                   = " << xi << '\n'
            << " <- mask                 = " << mask << '\n'
            << " -> bit_notand(xi, mask) = " << eve::bit_notand(xi, mask) << '\n';
  return 0;
}
