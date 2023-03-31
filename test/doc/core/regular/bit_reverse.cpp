#include <eve/wide.hpp>
#include <iostream>
#include <bit>


using wide_it = eve::wide<std::uint16_t, eve::fixed<4>>;

int main()
{
  wide_it pi = {-14, 1, 3, 0};
  auto _1 = std::integral_constant<size_t, 1>();
  auto _3 = std::integral_constant<size_t, 3>();
  auto _4 = std::integral_constant<size_t, 4>();

  std::cout << "---- simd" << '\n'
            << "<- pi                         = " << pi << '\n'
            << "-> bit_reverse(pi)            = " << eve::bit_reverse(pi) << '\n'
            << "-> sbit_reverse(pi)           = " << eve::detail::map(eve::bit_reverse, pi)<< '\n'
            << "-> bit_reverse(pi, _4)        = " << eve::bit_reverse(pi, _4)<< '\n'
            << "-> bit_reverse[pi>2](pi)      = " << eve::bit_reverse[pi > 2](pi)<< '\n'
            << "-> bit_reverse[pi > 2](pi, _4)= " << eve::bit_reverse[pi > 2](pi, _4)<< '\n'
    ;

 std::uint16_t xf = 0xff00;

  std::cout << "---- scalar" << '\n'
            << "<- xf                         = " << std::bitset<16>(xf) << '\n'
            << "-> bit_reverse(xf)            = " << std::bitset<16>(eve::bit_reverse(xf)) << '\n'
            << "-> bit_reverse(xf, _3)        = " << std::bitset<16>(eve::bit_reverse(xf, _3))<< '\n'
            << "-> bit_reverse(xf, _1)        = " << std::bitset<16>(eve::bit_reverse(xf, _1))<< '\n'
            << "-> bit_reverse[xf>2](xf)      = " << std::bitset<16>(eve::bit_reverse[xf > 2](xf)) << '\n'
            << "-> bit_reverse[xf > 2](xf, _4)= " << std::bitset<16>(eve::bit_reverse[xf > 2](xf, _4))<< '\n'
            << "-> bit_reverse[xf < 2](xf, _4)= " << std::bitset<16>(eve::bit_reverse[xf <  2](xf, _4))<< '\n'
  ;
  return 0;
}
