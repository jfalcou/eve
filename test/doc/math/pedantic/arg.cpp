#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<4>>;

int main()
{
  wide_ft pf = { 0.0f, 1.0f, eve::nan(eve::as(1.0f)), -eve::nan(eve::as(1.0f))};

  std::cout
    << "---- simd" << '\n'
    << "<- pf            = " << pf << '\n'
    << "-> eve::arg(pf)  = " << eve::arg(pf) << '\n';
  return 0;
}
