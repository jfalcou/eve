#include <eve/module/arithmetic/constant/maxexponent.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float>;

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::endl
            << "-> maxexponent(as<wide_ft>())  = " << eve::maxexponent(eve::as<wide_ft>()) << std::endl
            << "-> maxexponent(as(wxf))        = " << eve::maxexponent(eve::as(wxf))       << std::endl;

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> maxexponent(as<float>())         = " << eve::maxexponent(eve::as(float())) << std::endl
            << "-> maxexponent(as<xf))              = " << eve::maxexponent(eve::as(xf)) << std::endl;

  return 0;
}
