#include <eve/constant/sqrteps.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float>;

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::endl
            << "-> sqrteps(as<wide_ft>())  = " << eve::sqrteps(eve::as<wide_ft>()) << std::endl
            << "-> sqrteps(as(wxf))        = " << eve::sqrteps(eve::as(wxf))       << std::endl;

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> sqrteps(as<float>())         = " << eve::sqrteps(eve::as(float())) << std::endl
            << "-> sqrteps(as<xf))              = " << eve::sqrteps(eve::as(xf)) << std::endl;

  return 0;
}
