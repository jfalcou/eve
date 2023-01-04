#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::setprecision(9) << std::endl
            << "-> inv_pi(as<wide_ft>())       = " << eve::inv_pi(eve::as<wide_ft>())            << std::endl
            << "-> inv_pi(as(wxf))             = " << eve::inv_pi(eve::as(wxf))                  << std::endl;

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> inv_pi(as<float>())         = " << eve::inv_pi(eve::as(float())) << std::endl
            << "-> inv_pi(as<xf))              = " << eve::inv_pi(eve::as(xf))      << std::endl;

  return 0;
}
