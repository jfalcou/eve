#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float>;

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::endl
            << "-> exponentmask(as<wide_ft>())  = " << eve::exponentmask(eve::as<wide_ft>()) << std::endl
            << "-> exponentmask(as(wxf))        = " << eve::exponentmask(eve::as(wxf))       << std::endl;

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> exponentmask(as<float>())         = " << eve::exponentmask(eve::as(float())) << std::endl
            << "-> exponentmask(as<xf))              = " << eve::exponentmask(eve::as(xf)) << std::endl;

  return 0;
}
