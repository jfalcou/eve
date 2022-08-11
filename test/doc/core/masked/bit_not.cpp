#include <eve/wide.hpp>
#include <iostream>

using wide_it = eve::wide<std::uint32_t, eve::fixed<4>>;

int main()
{
  wide_it pi = {14, 1, 3, 0};

  std::cout << "---- simd" << '\n'
            << "<- pi          = " << pi << '\n'
            << "-> bit_not[pi > 2](pi) = " << eve::bit_not[pi > 2](pi) << '\n';

  return 0;
}
