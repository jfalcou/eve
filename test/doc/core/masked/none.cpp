#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;
using wide_it = eve::wide<std::int16_t, eve::fixed<4>>;

int main()
{
  wide_it qi = {-3, 0, -30, -32768};

  std::cout << "---- simd" << '\n'
            << "<- qi                             = " << qi << '\n'
            << "-> none[ignore_first(1)](qi != 0) = " << eve::none[eve::ignore_first(1)](qi != 0) << '\n';
  return 0;
}
