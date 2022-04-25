#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float>;

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::endl
            << "-> eta(as<wide_ft>())  = " << eve::eta(eve::as<wide_ft>()) << std::endl
            << "-> eta(as(wxf))        = " << eve::eta(eve::as(wxf))       << std::endl;

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> eta(as<float>())         = " << eve::eta(eve::as(float())) << std::endl
            << "-> eta(as<xf))              = " << eve::eta(eve::as(xf)) << std::endl;

  return 0;
}
