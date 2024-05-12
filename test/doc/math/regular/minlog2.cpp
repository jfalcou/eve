#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::setprecision(9) << std::endl
            << "-> minlog2(as<wide_ft>())        = " << eve::minlog2(eve::as<wide_ft>())            << std::endl
            << "-> minlog2(as(wxf))              = " << eve::minlog2(eve::as(wxf))                  << std::endl;

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> minlog2(as<float>())         = " << eve::minlog2(eve::as(float())) << std::endl
            << "-> minlog2(as<xf))              = " << eve::minlog2(eve::as(xf))      << std::endl;

  return 0;
}
