#include <eve/constant/twoopi.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float>;

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::endl
            << "-> twoopi(as<wide_ft>())  = " << eve::twoopi(eve::as<wide_ft>()) << std::endl
            << "-> twoopi(as(wxf))        = " << eve::twoopi(eve::as(wxf))       << std::endl;

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> twoopi(as<float>())         = " << eve::twoopi(eve::as(float())) << std::endl
            << "-> twoopi(as<xf))              = " << eve::twoopi(eve::as(xf)) << std::endl;

  return 0;
}
