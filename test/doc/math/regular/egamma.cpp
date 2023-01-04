#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::setprecision(9) << std::endl
            << "-> egamma(as<wide_ft>())       = " << eve::egamma(eve::as<wide_ft>())            << std::endl
            << "-> egamma(as(wxf))             = " << eve::egamma(eve::as(wxf))                  << std::endl;

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> egamma(as<float>())         = " << eve::egamma(eve::as(float())) << std::endl
            << "-> egamma(as<xf))              = " << eve::egamma(eve::as(xf))      << std::endl;

  return 0;
}
