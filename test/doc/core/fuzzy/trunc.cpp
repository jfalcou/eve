#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{
  float decr = -eve::eps(eve::as<float>());
  wide_ft pf = {-1.0f+decr, -1.0f+3*decr, -1.0f+5*decr, -1.7f, 2.0f, 2.0f+2*decr, 2.0f+5*decr, 2.7f};

  std::cout << "---- simd"  << std::setprecision(8) << '\n'
            << "<- pf                            = " << pf << '\n'
            << "-> trunc(pf)                     = " << eve::trunc(pf) << '\n'
            << "-> trunc[tolerant](pf)           = " << eve::trunc[eve::tolerant](pf)           << '\n'
            << "-> trunc[tolerance = 2*decr](pf) = " << eve::trunc[eve::tolerance = 2*decr](pf) << '\n'
            << "-> trunc[tolerance = 4](pf)      = " << eve::trunc[eve::tolerance = 4](pf)      << '\n';
  return 0;
}
