#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::setprecision(9) << std::endl
            << "-> sqrt_3(as<wide_ft>())        = " << eve::sqrt_3(eve::as<wide_ft>())            << std::endl
            << "-> sqrt_3(as(wxf))              = " << eve::sqrt_3(eve::as(wxf))                  << std::endl;

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> sqrt_3(as<float>())         = " << eve::sqrt_3(eve::as(float())) << std::endl
            << "-> sqrt_3(as<xf))              = " << eve::sqrt_3(eve::as(xf))      << std::endl;

  return 0;
}
