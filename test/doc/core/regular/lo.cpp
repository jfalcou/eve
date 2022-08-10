#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_uit = eve::wide<std::uint32_t, eve::fixed<8>>;
using wide_ui8t= eve::wide<std::uint8_t , eve::fixed<8>>;

int main()
{
  wide_uit i32 = {0, 1, 2, 3, 65536+1, 65536+8, 65536+16, 65536+32};
  wide_ui8t i8 = {0, 1, 2, 3, 16+0, 16+2, 16+4, 16+8};

  auto m   = eve::lo(i32);
  auto m8  = eve::lo(i8);
  std::cout << "---- simd (hexadecimal output)" << '\n'
            << std::hex
            << "<- i32             = " << i32 << '\n'
            << "-> lo(i32)         = " << m   << '\n'
            << std::hex << "<- i8  = " << i8  << '\n'
            << "-> lo(i8 )         = " << m8  << '\n';

  std::int32_t x = 100000;
  std::int8_t  y = 100;
  std::cout << "---- scalar (hexadecimal output)" << '\n'
            <<  std::hex << "<- x      = " << x   << '\n'
            << "-> lo(x)  = " << eve::lo(x) << '\n'
            << "<- y      = " << y   << '\n'
            << "-> lo(y)  = " << int(eve::lo(y)) << '\n' ;
  return 0;
}
