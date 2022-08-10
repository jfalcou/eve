#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_it = eve::wide<std::uint32_t, eve::fixed<8>>;

int main()
{
  wide_it pi = {14, 1, 3, 7, 20, 23000, 0, 27};

  std::cout << "---- simd" << '\n'
            << "<- pi                    = " << pi << '\n'
            << "-> bit_floor[pi > 4](pi) = " << eve::bit_floor[pi > 4](pi) << '\n';

  return 0;
}
