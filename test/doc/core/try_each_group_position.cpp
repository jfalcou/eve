#include <iostream>
#include <eve/module/core.hpp>

using wide_it = eve::wide<std::uint32_t, eve::fixed<4>>;

int main()
{
  wide_it x = {1, 2, 3, 4};

  std::cout << "---- simd" << '\n'
            << "<- x                                        = " << x << '\n'
            << "-> try_each_group_position(x, eve::lane<1>) = " << eve::try_each_group_position(x, eve::lane<1>) << '\n'
            << "-> try_each_group_position(x, eve::lane<2>) = " << eve::try_each_group_position(x, eve::lane<2>) << '\n';
}
