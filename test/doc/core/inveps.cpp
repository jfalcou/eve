#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::setprecision(9) << std::endl
            << "-> inveps(as<wide_ft>())        = " << eve::inveps(eve::as<wide_ft>())            << std::endl
            << "-> inveps(as(wxf))              = " << eve::inveps(eve::as(wxf))                  << std::endl;

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> inveps(as<float>())         = " << eve::inveps(eve::as(float())) << std::endl
            << "-> inveps(as<xf))              = " << eve::inveps(eve::as(xf))      << std::endl;

  return 0;
}
