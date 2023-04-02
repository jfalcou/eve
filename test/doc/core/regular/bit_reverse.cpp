#include <eve/wide.hpp>
#include <iostream>
#include <bit>


using wide_it = eve::wide<std::uint16_t, eve::fixed<4>>;

int main()
{
  wide_it pi = {-14, 1, 3, 0};

  std::cout << "---- simd" << '\n'
            << "<- pi                         = " << pi << '\n'
            << "-> bit_reverse(pi)            = " << eve::bit_reverse(pi) << '\n'
            << "-> sbit_reverse(pi)           = " << eve::detail::map(eve::bit_reverse, pi)<< '\n'
            << "-> bit_reverse(pi, 4)         = " << eve::bit_reverse(pi, 4)<< '\n'
            << "-> bit_reverse[pi>2](pi)      = " << eve::bit_reverse[pi > 2](pi)<< '\n'
            << "-> bit_reverse[pi > 2](pi, 4) = " << eve::bit_reverse[pi > 2](pi, 4)<< '\n'
    ;

 std::uint16_t xf = 0xff00;

  std::cout << "---- scalar" << '\n'
            << "<- xf                         = " << std::bitset<16>(xf) << '\n'
            << "-> bit_reverse(xf)            = " << std::bitset<16>(eve::bit_reverse(xf)) << '\n'
            << "-> bit_reverse(xf, 3)         = " << std::bitset<16>(eve::bit_reverse(xf, 3))<< '\n'
            << "-> bit_reverse(xf, 1)         = " << std::bitset<16>(eve::bit_reverse(xf, 1))<< '\n'
            << "-> bit_reverse[xf>2](xf)      = " << std::bitset<16>(eve::bit_reverse[xf > 2](xf)) << '\n'
            << "-> bit_reverse[xf > 2](xf, 4) = " << std::bitset<16>(eve::bit_reverse[xf > 2](xf, 4))<< '\n'
            << "-> bit_reverse[xf < 2](xf, 4) = " << std::bitset<16>(eve::bit_reverse[xf <  2](xf, 4))<< '\n'
  ;
  return 0;
}
