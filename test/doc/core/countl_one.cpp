#include <eve/wide.hpp>
#include <iostream>

using wide_it = eve::wide<std::uint32_t, eve::fixed<4>>;

int main()
{
  wide_it pi = {14, 1, 3, 0};

  std::cout << "---- simd" << '\n'
            << "<- pi             = " << pi << '\n'
            << "-> countl_one(pi) = " << eve::countl_one(pi) << '\n';

  std::uint32_t xf = 48;

  std::cout << "---- scalar" << '\n'
            << "<- xf             = " << xf << '\n'
            << "-> countl_one(xf) = " << eve::countl_one(xf) << '\n';
  return 0;
}
