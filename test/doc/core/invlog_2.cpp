#include <eve/module/math/constant/invlog_2.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float>;

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::endl
            << "-> invlog_2(as<wide_ft>())  = " << eve::invlog_2(eve::as<wide_ft>()) << std::endl
            << "-> invlog_2(as(wxf))        = " << eve::invlog_2(eve::as(wxf))       << std::endl;

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> invlog_2(as<float>())         = " << eve::invlog_2(eve::as(float())) << std::endl
            << "-> invlog_2(as<xf))              = " << eve::invlog_2(eve::as(xf)) << std::endl;

  return 0;
}
