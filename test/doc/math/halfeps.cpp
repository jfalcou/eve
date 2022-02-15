#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::setprecision(9) << std::endl
            << "-> halfeps(as<wide_ft>())       = " << eve::halfeps(eve::as<wide_ft>())            << std::endl
            << "-> halfeps(as(wxf))             = " << eve::halfeps(eve::as(wxf))                  << std::endl;

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> halfeps(as<float>())         = " << eve::halfeps(eve::as(float())) << std::endl
            << "-> halfeps(as<xf))              = " << eve::halfeps(eve::as(xf))      << std::endl;

  return 0;
}
