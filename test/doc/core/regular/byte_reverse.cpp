#include <eve/wide.hpp>
#include <iostream>

using wide_it = eve::wide<std::uint32_t, eve::fixed<4>>;

int main()
{
  wide_it pi = {257, 1, 3, 0};

  std::cout << "---- simd" << '\n'
            << "<- pi              = " << pi << '\n'
            << "-> byte_reverse(pi) = " << eve::byte_reverse(pi) << '\n';

  std::uint16_t xf = 48;

  std::cout << "---- scalar" << '\n'
            << "<- xf              = " << +xf << '\n'
            << "-> byte_reverse(xf) = " << +eve::byte_reverse(xf) << '\n';
  return 0;
}
