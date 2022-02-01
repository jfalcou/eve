#include <eve/module/math/constant/pi.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float>;

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::endl
            << "-> pi(as<wide_ft>())  = " << eve::pi(eve::as<wide_ft>()) << std::endl
            << "-> pi(as(wxf))        = " << eve::pi(eve::as(wxf))       << std::endl;

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> pi(as<float>())         = " << eve::pi(eve::as(float())) << std::endl
            << "-> pi(as<xf))              = " << eve::pi(eve::as(xf)) << std::endl;

  return 0;
}
