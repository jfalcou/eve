#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{
  wide_ft pf = {-1.0f, -1.3f, -1.5f, -1.7f, 2.0f, 2.3f, 2.5f, 2.7f};
  pf -= 3*eve::eps(eve::as<float>());

  std::cout << "---- simd"  << std::setprecision(8) << '\n'
            << "<- pf                     = " << pf << '\n'
            << "-> floor(pf)              = " << eve::floor(pf) << '\n'
            << "-> tolerant(floor)(pf)    = " << eve::tolerant(eve::floor)(pf) << '\n'
            << "-> tolerant(floor)(pf, 1) = " << eve::tolerant(eve::floor)(pf, 1) << '\n';
  return 0;
}
