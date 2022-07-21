#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_it = eve::wide<int16_t, eve::fixed<4>>;

int main()
{
  wide_it pf = {0, 1, -1, -eve::valmax(eve::as<int16_t>())};
  wide_it qf = {1, -1, 0, eve::valmax(eve::as<int16_t>())};

  std::cout << "---- simd" << '\n'
            << "<- pf                       = " << pf << '\n'
            << "<- qf                       = " << qf << '\n'
            << "-> saturated(dist)(pf, qf) = " << eve::saturated(eve::dist)(pf, qf)
            << '\n';
  return 0;
}
