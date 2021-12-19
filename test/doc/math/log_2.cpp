//#include <eve/constant/log_2.hpp>
#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float>;

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::endl
            << "-> log_2(as<wide_ft>())  = " << eve::log_2(eve::as<wide_ft>()) << std::endl
            << "-> log_2(as(wxf))        = " << eve::log_2(eve::as(wxf))       << std::endl;

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> log_2(as<float>())         = " << eve::log_2(eve::as(float())) << std::endl
            << "-> log_2(as<xf))              = " << eve::log_2(eve::as(xf)) << std::endl;

  return 0;
}
