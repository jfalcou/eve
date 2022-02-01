#include <eve/module/math/constant/invpi.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float>;

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::endl
            << "-> invpi(as<wide_ft>())  = " << eve::invpi(eve::as<wide_ft>()) << std::endl
            << "-> invpi(as(wxf))        = " << eve::invpi(eve::as(wxf))       << std::endl;

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> invpi(as<float>())         = " << eve::invpi(eve::as(float())) << std::endl
            << "-> invpi(as<xf))              = " << eve::invpi(eve::as(xf)) << std::endl;

  return 0;
}
