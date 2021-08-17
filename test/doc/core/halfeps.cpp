#include <eve/constant/halfeps.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float>;

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::endl
            << "-> halfeps(as<wide_ft>())  = " << eve::halfeps(eve::as<wide_ft>()) << std::endl
            << "-> halfeps(as(wxf))        = " << eve::halfeps(eve::as(wxf))       << std::endl;

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> halfeps(as<float>())         = " << eve::halfeps(eve::as(float())) << std::endl
            << "-> halfeps(as<xf))              = " << eve::halfeps(eve::as(xf)) << std::endl;

  return 0;
}
