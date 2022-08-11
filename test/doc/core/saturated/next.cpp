#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft pf = {0.0f, 2.0f, eve::inf(eve::as<float>()), eve::nan(eve::as<float>())};

  std::cout << "---- simd" << '\n'
            << "<- pf                   = " << std::setprecision(12) << pf << '\n'
            << "-> saturated(next)(pf)  = " << eve::saturated(eve::next)(pf) << '\n';
  return 0;
}
