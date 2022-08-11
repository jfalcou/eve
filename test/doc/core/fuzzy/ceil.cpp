#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{
  wide_ft pf = {-1.0f, -1.3f, -1.5f, -1.7f, 2.0f, 2.3f, 2.5f, 2.7f};
  pf += 3*eve::eps(eve::as<float>());

  std::cout << "---- simd" << std::setprecision(8) << '\n'
            << "<- pf                     = " << pf << '\n'
            << "-> ceil(pf)               = " << eve::ceil(pf) << '\n'
            << "-> tolerant(ceil)(pf)     = " << eve::tolerant(eve::ceil)(pf) << '\n'
            << "-> tolerant(ceil)(pf, 1)  = " << eve::tolerant(eve::ceil)(pf, 1) << '\n';
  return 0;
}
