#include <iostream>
#include <eve/module/core.hpp>

using wide_it = eve::wide<std::uint64_t, eve::fixed<4>>;

int main()
{
  wide_it x = {1, 2, 3, 4};

  std::cout << "---- simd" << '\n'
            << "<- x                        = " << x << '\n'
            << "-> rotate(x, eve::index<0>) = " << eve::rotate(x, eve::index<0>) << '\n'
            << "-> rotate(x, eve::index<1>) = " << eve::rotate(x, eve::index<1>) << '\n'
            << "-> rotate(x, eve::index<2>) = " << eve::rotate(x, eve::index<2>) << '\n'
            << "-> rotate(x, eve::index<3>) = " << eve::rotate(x, eve::index<3>) << '\n'
            << "-> rotate(x, eve::index<4>) = " << eve::rotate(x, eve::index<4>) << '\n';

}
