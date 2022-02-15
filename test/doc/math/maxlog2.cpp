#include <eve/module/core.hpp>
#include <eve/module/math/constant/maxlog2.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::setprecision(9) << std::endl
            << "-> maxlog2(as<wide_ft>())        = " << eve::maxlog2(eve::as<wide_ft>())            << std::endl
            << "-> maxlog2(as(wxf))              = " << eve::maxlog2(eve::as(wxf))                  << std::endl;

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> maxlog2(as<float>())         = " << eve::maxlog2(eve::as(float())) << std::endl
            << "-> maxlog2(as<xf))              = " << eve::maxlog2(eve::as(xf))      << std::endl;

  return 0;
}
