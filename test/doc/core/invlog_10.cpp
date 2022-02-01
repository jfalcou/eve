#include <eve/module/math/constant/invlog_10.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float>;

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::endl
            << "-> invlog_10(as<wide_ft>())  = " << eve::invlog_10(eve::as<wide_ft>()) << std::endl
            << "-> invlog_10(as(wxf))        = " << eve::invlog_10(eve::as(wxf))       << std::endl;

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> invlog_10(as<float>())         = " << eve::invlog_10(eve::as(float())) << std::endl
            << "-> invlog_10(as<xf))              = " << eve::invlog_10(eve::as(xf)) << std::endl;

  return 0;
}
