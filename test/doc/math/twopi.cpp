#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::setprecision(9) << std::endl
            << "-> twopi(as<wide_ft>())       = " << eve::twopi(eve::as<wide_ft>())            << std::endl
            << "-> twopi(as(wxf))             = " << eve::twopi(eve::as(wxf))                  << std::endl;

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> twopi(as<float>())         = " << eve::twopi(eve::as(float())) << std::endl
            << "-> twopi(as<xf))              = " << eve::twopi(eve::as(xf))      << std::endl;

  return 0;
}
