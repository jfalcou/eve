#include <eve/module/core.hpp>
#include <eve/module/math/constant/minlog10denormal.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::setprecision(9) << std::endl
            << "-> minlog10denormal(as<wide_ft>())        = " << eve::minlog10denormal(eve::as<wide_ft>())            << std::endl
            << "-> minlog10denormal(as(wxf))              = " << eve::minlog10denormal(eve::as(wxf))                  << std::endl;

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> minlog10denormal(as<float>())         = " << eve::minlog10denormal(eve::as(float())) << std::endl
            << "-> minlog10denormal(as<xf))              = " << eve::minlog10denormal(eve::as(xf))      << std::endl;

  return 0;
}
