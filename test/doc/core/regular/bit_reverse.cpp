#include <eve/wide.hpp>
#include <iostream>

using wide_it = eve::wide<std::uint32_t, eve::fixed<4>>;

int main()
{
  wide_it pi = {14, 1, 3, 0};

  std::cout << "---- simd" << '\n'
            << "<- pi              = " << pi << '\n'
            << "-> bit_reverse(pi) = " << eve::bit_reverse(pi) << '\n';

  std::uint8_t xf = 48;

  std::cout << "---- scalar" << '\n'
            << "<- xf              = " << +xf << '\n'
            << "-> bit_reverse(xf) = " << +eve::bit_reverse(xf) << '\n';
  return 0;
}
