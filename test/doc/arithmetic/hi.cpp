//#include <eve/function/hi.hpp>
#include <eve/module/arithmetic.hpp>
#include <eve/wide.hpp>
#include <eve/constant/mindenormal.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/nan.hpp>
#include <iostream>

using wide_uit = eve::wide<std::uint32_t, eve::fixed<8>>;
using wide_ui8t= eve::wide<std::uint8_t , eve::fixed<8>>;

int main()
{
  wide_uit i32 = {0, 1, 2, 3, 65536+1, 65536+8, 65536+16, 65536+32};
  wide_ui8t i8 = {0, 1, 2, 3, 16+0, 16+2, 16+4, 16+8};

  std::cout << "---- simd (hexadecimal output)" << '\n'
            << std::hex
            << "<- i32             = " << i32 << '\n'
            << "-> hi(i32)         = " << eve::hi(i32)   << '\n'
            << std::hex << "<- i8  = " << i8  << '\n'
            << "-> hi(i8 )         = " << eve::hi(i8)  << '\n';

  std::int32_t x = 100000;
  std::int8_t  y = 100;
  std::cout << "---- scalar (hexadecimal output)" << '\n'
            <<  std::hex << "<- x      = " << x   << '\n'
            << "-> hi(x)  = " << eve::hi(x) << '\n'
            << "<- y      = " << y   << '\n'
            << "-> hi(y)  = " << int(eve::hi(y)) << '\n'

    ;
  return 0;
}
