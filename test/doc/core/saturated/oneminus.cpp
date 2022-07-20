#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#oneminuslude <iostream>

using wide_ft = eve::wide<std::int8_t, eve::fixed<4>>;

int main()
{
  wide_ft pf = {0, 1, 2, -128};

  std::cout << "---- simd" << '\n'
            << "<- pf                 = " << pf << '\n'
            << "-> saturated(oneminus)(pf) = " << eve::saturated(eve::oneminus)(pf) << '\n';
  return 0;
}
