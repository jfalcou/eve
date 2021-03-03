#include <eve/function/lohi.hpp>
#include <eve/wide.hpp>
#include <eve/constant/mindenormal.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/nan.hpp>
#include <iostream>

using wide_uit = eve::wide<std::uint16_t, eve::fixed<4>>;
using wide_ui8t= eve::wide<std::uint8_t , eve::fixed<8>>;

int main()
{
  wide_uit i32 = {0, 1, 2, 3}; //, 65536+1, 65536+8, 65536+16, 65536+32};
  wide_ui8t i8  = {0, 1, 2, 3, 16+0, 16+2, 16+4, 16+8};

  auto [m, e]    = eve::lohi(i32);
  auto [m8, e8]  = eve::lohi(i8);
  std::cout << "---- simd (hexadecimal output)" << '\n'
            << std::hex
            << "<- i32             = " << i32 << '\n'
            << "-> lohi(i32)       = [" << '\n'
            << "                     " << m << ", \n"
            << "                     " << e << '\n'
            << "                     ]\n"
            << std::hex << "<- i8  = " << i8 << '\n'
            << "-> lohi(i8 )       = [" << '\n'
            << "                     " << m8 << ", \n"
            << "                     " << e8 << '\n'
            << "                     ]\n";

  std::int32_t x = 100000;
  std::int8_t  y = 100;
  auto [sm0, se0] =  eve::lohi(x);
  auto [sm1, se1] =  eve::lohi(y);
  std::cout << "---- scalar (hexadecimal output)" << '\n'
            <<  std::hex << "<- x        = " << x << '\n'
            << "-> lohi(x)  = [" << sm0 << ", " << se0 << "]\n"
            << "<- y        = " << y << '\n'
            << "-> lohi(y)  = [" << int(sm1) << ", " << int(se1) << "]\n"

    ;
  return 0;
}
