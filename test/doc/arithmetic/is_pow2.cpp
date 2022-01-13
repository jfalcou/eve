//#include <eve/function/is_pow2.hpp>
#include <eve/module/arithmetic.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_it = eve::wide<std::uint32_t, eve::fixed<8>>;

int main()
{
  wide_it pi = {14, 1, 3, 0, 16, 23000, 0, 27};

  std::cout << "---- simd" << '\n'
            << "<- pi          = " << pi << '\n'
            << "-> is_pow2(pi) = " << eve::is_pow2(pi) << '\n';

  std::uint32_t xf = 48;

  std::cout << "---- scalar" << '\n'
            << "<- xf          = " << xf << '\n'
            << "-> is_pow2(xf) = " << eve::is_pow2(xf) << '\n';
  return 0;
}
