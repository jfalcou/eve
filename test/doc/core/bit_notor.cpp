#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using w_t = eve::wide<std::uint32_t, eve::fixed<4>>;
  w_t pi = {3, 2, 3, 4}, qi = {4, 1, 1, ~0};
  std::uint32_t z = 5;
  std::cout << "---- simd" << '\n'
            << " <- pi                       = " << pi << '\n'
            << " <- qi                       = " << qi << '\n'
            << " <- z                        = " << z  << '\n'
            << " -> bit_notor(pi, qi)        = " << eve::bit_notor(pi, qi) << '\n'
            << " -> bit_notor(qi, z)         = " << eve::bit_notor(qi,  z) << '\n'
            << " -> bit_notor(pi, z )        = " << eve::bit_notor(pi, z) << '\n'
            << " -> bit_notor[pi<qi](pi, qi) = " << eve::bit_notor[pi<qi](pi, qi) << '\n';

  std::uint32_t mask = 1 >> 31;
  float xi = -3.4565;

  std::cout << "---- scalar" << '\n'
            << " <- xi                  = " << xi << '\n'
            << " <- mask                = " << mask << '\n'
            << " -> bit_notor(xi, mask) = " << eve::bit_notor(xi, mask) << '\n';
  return 0;
}
