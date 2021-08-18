#include <eve/constant/maxflint.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float>;

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::endl
            << "-> maxflint(as<wide_ft>())  = " << eve::maxflint(eve::as<wide_ft>()) << std::endl
            << "-> maxflint(as(wxf))        = " << eve::maxflint(eve::as(wxf))       << std::endl;

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> maxflint(as<float>())         = " << eve::maxflint(eve::as(float())) << std::endl
            << "-> maxflint(as<xf))              = " << eve::maxflint(eve::as(xf)) << std::endl;

  return 0;
}
