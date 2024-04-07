#include <eve/wide.hpp>
#include <iostream>
#include <bit>
#include <eve/module/core.hpp>

using wide_it = eve::wide<std::uint32_t, eve::fixed<8>>;

int main()
{
  wide_it pi = {1, 3, 7, 15, 31, 63, 127, 255};

  std::cout << "---- simd" << '\n'
            << "<- pi                          = " << pi << '\n'
            << "-> first_true(pi > 1).value_or(-1)                      = " << eve::first_true(pi > 1).value_or(-1) << '\n'
            << "-> first_true(pi > 2).value_or(-1)                      = " << eve::first_true(pi > 2).value_or(-1) << '\n'
            << "-> first_true(pi > 35).value_or(-1)                     = " << eve::first_true(pi > 35).value_or(-1) << '\n'
            << "-> first_true(pi > 1000).value_or(-1)                   = " << eve::first_true(pi > 1000).value_or(-1) << '\n'
            << "-> first_true[eve::ignore_first(2)](pi<10).value_or(-1) = " << eve::first_true[eve::ignore_first(2)](pi< 10).value_or(-1) << '\n';

  return 0;
}
