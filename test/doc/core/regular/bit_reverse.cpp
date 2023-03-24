#include <eve/wide.hpp>
#include <iostream>
#include <bit>


using wide_it = eve::wide<std::uint64_t, eve::fixed<4>>;

int main()
{
  wide_it pi = {-14, 1, 3, 0};

  std::cout << "---- simd" << '\n'
            << "<- pi              = " << pi << '\n'
            << "-> bit_reverse(pi)  = " << eve::bit_reverse(pi) << '\n'
            << "-> sbit_reverse(pi) = " << eve::detail::map(eve::bit_reverse, pi)<< '\n'
    ;

  std::uint64_t xf = (-14);
  xf = xf >> 1;

  std::cout << "---- scalar" << '\n'
            << "<- xf              = " << std::bitset<64>(xf) << '\n'
            << "-> bit_reverse(xf) = " << std::bitset<64>(eve::bit_reverse(xf)) << '\n'

    ;
  return 0;
}
