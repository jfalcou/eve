#include <eve/module/core.hpp>
#include <eve/module/math/constant/oneotwoeps.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::setprecision(9) << std::endl
            << "-> oneotwoeps(as<wide_ft>())        = " << eve::oneotwoeps(eve::as<wide_ft>())            << std::endl
            << "-> oneotwoeps(as(wxf))              = " << eve::oneotwoeps(eve::as(wxf))                  << std::endl;

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> oneotwoeps(as<float>())         = " << eve::oneotwoeps(eve::as(float())) << std::endl
            << "-> oneotwoeps(as<xf))              = " << eve::oneotwoeps(eve::as(xf))      << std::endl;

  return 0;
}
