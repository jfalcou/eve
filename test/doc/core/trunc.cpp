#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{
  float decr = eve::eps(eve::as<float>());
  wide_ft pf = {-1.0f, -1.3f, -1.5f, -1.7f, 1.0f, 2.3f, 2.5f, 2.7f};
  auto  pf1 = eve::prev[pf >  0](pf, 7);
  pf1 = eve::next[pf < 0](pf1, 7);
  auto  pf2 = pf-eve::signnz(pf)*4.0f*decr;

  std::cout << "---- simd" << std::setprecision(9) << '\n'
            << "<- pf                               = " << pf  << '\n'
            << "<- pf1                              = " << pf1 << '\n'
            << "<- pf2                              = " << pf2 << '\n'
            << "-> trunc(pf)                        = " << eve::trunc(pf) << '\n'
            << "-> trunc[almost](pf)                = " << eve::trunc[eve::almost](pf)           << '\n'
            << "-> trunc[almost = 6](pf1)           = " << eve::trunc[eve::almost = 6](pf1)      << '\n'
            << "-> trunc[almost](pf1)               = " << eve::trunc[eve::almost](pf1)           << '\n'
            << "-> trunc[almost = 8](pf1)           = " << eve::trunc[eve::almost = 8](pf1)      << '\n'
            << "-> trunc[almost = 2.0f*decr](pf2)   = " << eve::trunc[eve::almost = 2.0f*decr](pf2) << '\n'
            << "-> trunc[almost](pf2)               = " << eve::trunc[eve::almost](pf2)           << '\n'
            << "-> trunc[almost = 5.0f*decr](pf2)   = " << eve::trunc[eve::almost = 5.0f*decr](pf2) << '\n';

  float xf = -32.768f;

  std::cout << "---- scalar" << '\n'
            << "<- xf        = " << xf << '\n'
            << "-> trunc(xf) = " << eve::trunc(xf) << '\n';

  return 0;
}
