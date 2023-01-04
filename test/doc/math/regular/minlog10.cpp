#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::setprecision(9) << std::endl
            << "-> minlog10(as<wide_ft>())        = " << eve::minlog10(eve::as<wide_ft>())            << std::endl
            << "-> minlog10(as(wxf))              = " << eve::minlog10(eve::as(wxf))                  << std::endl;

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> minlog10(as<float>())         = " << eve::minlog10(eve::as(float())) << std::endl
            << "-> minlog10(as<xf))              = " << eve::minlog10(eve::as(xf))      << std::endl;

  return 0;
}
