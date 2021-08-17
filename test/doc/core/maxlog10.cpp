#include <eve/constant/maxlog10.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float>;

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::endl
            << "-> maxlog10(as<wide_ft>())  = " << eve::maxlog10(eve::as<wide_ft>()) << std::endl
            << "-> maxlog10(as(wxf))        = " << eve::maxlog10(eve::as(wxf))       << std::endl; 

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> maxlog10(as<float>())         = " << eve::maxlog10(eve::as(float())) << std::endl
            << "-> maxlog10(as<xf))              = " << eve::maxlog10(eve::as(xf)) << std::endl; 

  return 0;
}
