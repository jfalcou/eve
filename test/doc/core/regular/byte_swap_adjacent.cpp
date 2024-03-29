
#include <eve/wide.hpp>
#include <iostream>
#include <eve/module/core.hpp>

using wide_it = eve::wide<std::uint32_t, eve::fixed<4>>;

int main()
{
  wide_it pi = {0x0fU, 0x0f0fU, 0x0f0f0fU, 0x0f0f0f0f0fU};

  std::cout << "---- simd" << '\n'
            << "<- pi                        = " << pi << '\n'
            << "-> byte_swap_adjacent(pi, 0) = " << eve::byte_swap_adjacent(pi, 0) << '\n'
            << "-> byte_swap_adjacent(pi, 1) = " << eve::byte_swap_adjacent(pi, 1) << '\n'
            << "-> byte_swap_adjacent(pi, 2) = " << eve::byte_swap_adjacent(pi, 2) << '\n'
            << "-> byte_swap_adjacent(pi, 4) = " << eve::byte_swap_adjacent(pi, 4) << '\n';


  std::uint64_t xf = 0xff00ff00ff00ff00ULL;

  std::cout << "---- scalar" << '\n'
            << "<- xf                        = " << std::hex << "0x" << xf << '\n'
            << "-> byte_swap_adjacent(xf, 1) = " << std::hex << "0x00" << eve::byte_swap_adjacent(xf,1) << '\n';
  return 0;
}
