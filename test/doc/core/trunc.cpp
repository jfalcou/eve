#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{
  float decr = -eve::eps(eve::as<float>());
  wide_ft pf = {-1.0f, -1.3f, -1.5f, -1.7f, 2.0f, 2.3f, 2.5f, 2.7f};

  std::cout << "---- simd" << '\n'
            << "<- pf                            = " << pf << '\n'
            << "-> trunc(pf)                     = " << eve::trunc(pf) << '\n'
            << "-> trunc[almost2](pf)            = " << eve::trunc[eve::almost2](pf)           << '\n'
            << "-> trunc[almost2 = 2*decr](pf)   = " << eve::trunc[eve::almost2 = 2*decr](pf) << '\n'
            << "-> trunc[almost2 = 4](pf)        = " << eve::trunc[eve::almost2 = 4](pf)      << '\n';
  return 0;
  float xf = -32.768f;

  std::cout << "---- scalar" << '\n'
            << "<- xf        = " << xf << '\n'
            << "-> trunc(xf) = " << eve::trunc(xf) << '\n';

  return 0;
}
