#include <eve/module/core.hpp>
#include <iostream>
#include <bit>


using wide_it = eve::wide<std::uint16_t, eve::fixed<4>>;

int main()
{
  wide_it pi = {-14, 1, 3, 0};

  std::cout << "---- simd" << '\n'
            << "<- pi                               = " << pi << '\n'
            << "-> bit_reverse[pi>0](pi)            = " << eve::bit_reverse[pi>0](pi) << '\n'
            << "-> bit_reverse[pi>0](pi, 4)         = " << eve::bit_reverse[pi>0](pi, 4)<< '\n'
            << "-> bit_reverse[pi>0](pi)            = " << eve::bit_reverse[pi>0](pi)<< '\n'
            << "-> bit_reverse[pi>0][pi > 2](pi, 4) = " << eve::bit_reverse[pi>0](pi, 4)<< '\n'
    ;

  return 0;
}
