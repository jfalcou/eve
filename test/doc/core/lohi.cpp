#include <eve/function/lohi.hpp>
#include <eve/wide.hpp>
#include <eve/constant/mindenormal.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/nan.hpp>
#include <iostream>

using wide_uit = eve::wide<std::uint32_t, eve::fixed<8>>;

int main()
{
  wide_uit i32 = {0, 1,  2,  3,  4, 65536, 65537, 65538};

  auto [m, e]    = eve::lohi(i32);
  std::cout << "---- simd" << '\n'
            << "<- i32                   = " << i32 << '\n'
            << "-> lohi(i32)             = [" << '\n'
            << "                          " << m << ", \n"
            << "                          " << e << '\n'
            << "                          ]\n";

  std::int32_t x = 100;
  auto [sm, se] =  eve::lohi(x);

  std::cout << "---- scalar" << '\n'
            << "<- x        =  " << x << '\n'
            << "-> lohi(x ) = [" << sm << ", " << se << "]\n";
  return 0;
}
