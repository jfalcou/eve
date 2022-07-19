#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<std::int8_t, eve::fixed<4>>;

int main()
{
  wide_ft pf = {0f, 1f, -127, -128};

  std::cout << "---- simd" << '\n'
            << "<- pf                 = " << pf << '\n'
            << "-> saturated(dec)(pf) = " << eve::saturated(eve::dec)(pf) << '\n';
  return 0;
}
