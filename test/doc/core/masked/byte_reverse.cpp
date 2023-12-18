#include <eve/module/core.hpp>
#include <iostream>

using wide_it = eve::wide<std::uint32_t, eve::fixed<4>>;

int main()
{
  wide_it pi = {257, 1, 3, 0};

  std::cout << "---- simd" << '\n'
            << "<- pi                     = " << pi << '\n'
            << "-> byte_reverse[pi<2](pi) = " << eve::byte_reverse[pi<2](pi) << '\n';

  return 0;
}
