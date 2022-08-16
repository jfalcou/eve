#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;
using wide_it = eve::wide<std::int16_t, eve::fixed<4>>;

int main()
{
  wide_ft pf = {-1.0f, 2.0f, -3.0f, 182.0f};

  std::cout << "---- simd" << '\n'
            << "<- pf                  = " << pf << '\n'
            << "-> sqr_abs[pf < 0](pf) = " << eve::sqr_abs[pf < 0](pf) << '\n';
  return 0;
}
