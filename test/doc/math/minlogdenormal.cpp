#include <eve/module/core.hpp>
#include <eve/module/math/constant/minlogdenormal.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::setprecision(9) << std::endl
            << "-> minlogdenormal(as<wide_ft>())        = " << eve::minlogdenormal(eve::as<wide_ft>())            << std::endl
            << "-> minlogdenormal(as(wxf))              = " << eve::minlogdenormal(eve::as(wxf))                  << std::endl;

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> minlogdenormal(as<float>())         = " << eve::minlogdenormal(eve::as(float())) << std::endl
            << "-> minlogdenormal(as<xf))              = " << eve::minlogdenormal(eve::as(xf))      << std::endl;

  return 0;
}
