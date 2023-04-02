
#include <eve/wide.hpp>
#include <iostream>
#include <bit>
#include <eve/module/core.hpp>

using wide_it = eve::wide<std::uint16_t, eve::fixed<8>>;

int main()
{
  wide_it pi = {1, 3, 7, 15, 31, 63, 127, 255};

  std::cout << "---- simd" << '\n'
            << "<- pi                        = " << pi << '\n'
            << "-> bit_swap_pairs(pi, 0, 15) = " << eve::bit_swap_pairs(pi, 0, 15) << '\n'
            << "-> bit_swap_pairs(pi, 2, 7 ) = " << eve::bit_swap_pairs(pi, 2, 7) << '\n';

  return 0;
}
