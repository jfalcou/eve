#include <eve/function/bit_reverse.hpp>
#include <eve/literals.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using w_t = eve::wide<std::uint8_t, eve::fixed<16>>;
  w_t p = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
  std::cout << "---- simd" << '\n'
            << " <- p               = " <<   std::hex << p << '\n'
            << " -> bit_reverse(p)  = " <<   std::hex << eve::bit_reverse(p) << '\n';


  std::uint8_t x = 1;

  std::cout << "---- scalar" << '\n'
            << " <- x                = " << std::bitset<8>(x) << '\n'
            << " -> bit_reverse(x)   = " << std::bitset<8>(eve::bit_reverse(x)) << '\n';

  return 0;
}
