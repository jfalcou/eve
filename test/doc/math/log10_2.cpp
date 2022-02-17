#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::setprecision(9) << std::endl
            << "-> invsqrtpi(as<wide_ft>())       = " << eve::invsqrtpi(eve::as<wide_ft>())            << std::endl
            << "-> invsqrtpi(as(wxf))             = " << eve::invsqrtpi(eve::as(wxf))                  << std::endl;

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> invsqrtpi(as<float>())         = " << eve::invsqrtpi(eve::as(float())) << std::endl
            << "-> invsqrtpi(as<xf))              = " << eve::invsqrtpi(eve::as(xf))      << std::endl;

  return 0;
}
