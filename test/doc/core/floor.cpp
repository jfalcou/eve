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
            << "-> floor(pf)                     = " << eve::floor(pf) << '\n'
            << "-> floor[almost2](pf)           = " << eve::floor[eve::almost2](pf)           << '\n'
            << "-> floor[almost2 = 2*decr](pf) = " << eve::floor[eve::almost2 = 2*decr](pf) << '\n'
            << "-> floor[almost2 = 4](pf)      = " << eve::floor[eve::almost2 = 4](pf)      << '\n'
            << "-> floor[pf>1.5](pf)             = " << eve::floor[pf>1.5](pf) << '\n';

  float xf = -32.768f;

  std::cout << "---- scalar" << '\n'
            << "<- xf        = " << xf << '\n'
            << "-> floor(xf) = " << eve::floor(xf) << '\n';
  return 0;
}
