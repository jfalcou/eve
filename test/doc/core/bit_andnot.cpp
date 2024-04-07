
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using w_t = eve::wide<std::int32_t, eve::fixed<4>>;
  w_t pi = {3, 2, 3, 4}, qi = {4, 1, 1, ~0};
  std::uint32_t z = 5;
  std::cout << "---- simd" << '\n'
            << " <- pi                        = " << pi << '\n'
            << " <- qi                        = " << qi << '\n'
            << " <- z                         = " << z  << '\n'
            << " -> bit_andnot(pi, qi)        = " << eve::bit_andnot(pi, qi) << '\n'
            << " -> bit_andnot(qi, z )        = " << eve::bit_andnot(qi, z) << '\n'
            << " -> bit_andnot(pi, z )        = " << eve::bit_andnot(pi, z) << '\n'
            << " -> bit_andnot[pi<qi](pi, qi) = " << eve::bit_andnot[pi<qi](pi, qi) << '\n';

  std::uint32_t mask = 1 << 31;
  float xi = -3.4565f;

  std::cout << "---- scalar" << '\n'
            << " <- xi                   = " << xi << '\n'
            << " <- mask                 = " << mask << '\n'
            << " -> bit_andnot(xi, mask) = " << eve::bit_andnot(xi, mask) << '\n';
  return 0;
}
