#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft pf = {0.0f, 2.0f, eve::minf(eve::as<float>()), eve::nan(eve::as<float>())};

  std::cout << "---- simd" << '\n'
            << "<- pf                   = " << std::setprecision(12) << pf << '\n'
            << "-> saturated(prev)(pf)  = " << eve::saturated(eve::prev)(pf) << '\n';
  return 0;
}
