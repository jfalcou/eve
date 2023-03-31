
#include <eve/wide.hpp>
#include <iostream>
#include <eve/module/core.hpp>

using wide_it = eve::wide<std::uint64_t, eve::fixed<8>>;

int main()
{
  wide_it pi = {1, 2, 3, 4, 5, 6, 7, 8};
  constexpr auto _1 = eve::fixed<1>();
  constexpr auto _2 = eve::fixed<2>();
  constexpr auto _4 = eve::fixed<4>();
  constexpr auto _8 = eve::fixed<8>();

  std::cout << "---- simd" << '\n'
            << "<- pi              = " << pi << '\n'
            << "-> swap_adjacent_groups(pi, _1) = " << eve::swap_adjacent_groups(pi, _1) << '\n'
            << "-> swap_adjacent_groups(pi, _2) = " << eve::swap_adjacent_groups(pi, _2) << '\n'
            << "-> swap_adjacent_groups(pi, _4) = " << eve::swap_adjacent_groups(pi, _4) << '\n'
            << "-> swap_adjacent_groups(pi, _8) = " << eve::swap_adjacent_groups(pi, _8) << '\n'
;

}
