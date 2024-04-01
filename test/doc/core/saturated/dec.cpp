#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<std::int8_t, eve::fixed<4>>;

int main()
{
  wide_ft pf = {0, 1, -127, -128};

  std::cout << "---- simd" << '\n'
            << "<- pf                 = " << pf << '\n'
            << "-> dec[saturated](pf) = " << eve::dec[eve::saturated](pf) << '\n';
  return 0;
}
