
#include <eve/wide.hpp>
#include <iostream>
#include <bit>
#include <eve/module/core.hpp>

using wide_it = eve::wide<std::uint16_t, eve::fixed<8>>;

int main()
{
  wide_it pi = {1, 3, 7, 15, 31, 63, 127, 255};
  auto _0 = std::integral_constant<size_t, 0>();
  auto _1 = std::integral_constant<size_t, 1>();

  std::cout << "---- simd" << '\n'
            << "<- pi              = " << pi << '\n'
            << "-> byte_swap_pairs[pi <  7](pi, _0, _1)) = " << eve::byte_swap_pairs[pi <  7](pi, _0, _1) << '\n';

  return 0;
}
