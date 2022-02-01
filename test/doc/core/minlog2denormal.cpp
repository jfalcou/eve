#include <eve/module/math/constant/minlog2denormal.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float>;

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::endl
            << "-> minlog2denormal(as<wide_ft>())  = " << eve::minlog2denormal(eve::as<wide_ft>()) << std::endl
            << "-> minlog2denormal(as(wxf))        = " << eve::minlog2denormal(eve::as(wxf))       << std::endl;

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> minlog2denormal(as<float>())         = " << eve::minlog2denormal(eve::as(float())) << std::endl
            << "-> minlog2denormal(as<xf))              = " << eve::minlog2denormal(eve::as(xf)) << std::endl;

  return 0;
}
