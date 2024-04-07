#include <iostream>
#include <eve/module/core.hpp>

using wide_it = eve::wide<std::uint32_t, eve::fixed<4>>;

int main()
{
  wide_it x = {2, 1, 2, 4};
  wide_it y = {0, 2, 3, 1};

  std::cout << "---- simd" << '\n'
            << "<- x                  = " << x << '\n'
            << "<- y                  = " << y << '\n'
            << "-> has_equal_in(x, y) = " << eve::has_equal_in(x, y) << '\n'
            << "-> has_equal_in(y, x) = " << eve::has_equal_in(y, x) << '\n';
}
