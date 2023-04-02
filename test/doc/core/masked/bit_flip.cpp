
#include <eve/wide.hpp>
#include <iostream>
#include <bit>
#include <eve/module/core.hpp>

using wide_it = eve::wide<std::uint16_t, eve::fixed<8>>;

int main()
{
  wide_it pi = {1, 3, 7, 15, 31, 63, 127, 255};

  std::cout << "---- simd" << '\n'
            << "<- pi                  = " << pi << '\n'
            << "-> bit_flip[pi > 15](pi, 1) = " << eve::bit_flip[pi > 15](pi, 1) << '\n'
            << "-> bit_flip[pi > 15](pi, 2) = " << eve::bit_flip[pi > 15](pi, 2) << '\n'
            << "-> bit_flip[pi > 15](pi, 3) = " << eve::bit_flip[pi > 15](pi, 3) << '\n'
            << "-> bit_flip[pi > 15](pi, 4) = " << eve::bit_flip[pi > 15](pi, 4) << '\n'
            << "-> bit_flip[pi > 15](pi, 8) = " << eve::bit_flip[pi > 15](pi, 8) << '\n';

  return 0;
}
