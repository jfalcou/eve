#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::setprecision(9) << std::endl
            << "-> minlog(as<wide_ft>())        = " << eve::minlog(eve::as<wide_ft>())            << std::endl
            << "-> minlog(as(wxf))              = " << eve::minlog(eve::as(wxf))                  << std::endl;

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> minlog(as<float>())         = " << eve::minlog(eve::as(float())) << std::endl
            << "-> minlog(as<xf))              = " << eve::minlog(eve::as(xf))      << std::endl;

  return 0;
}
