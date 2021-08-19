#include <eve/constant/maxlog.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float>;

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::endl
            << "-> maxlog(as<wide_ft>())  = " << eve::maxlog(eve::as<wide_ft>()) << std::endl
            << "-> maxlog(as(wxf))        = " << eve::maxlog(eve::as(wxf))       << std::endl;

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> maxlog(as<float>())         = " << eve::maxlog(eve::as(float())) << std::endl
            << "-> maxlog(as<xf))              = " << eve::maxlog(eve::as(xf)) << std::endl;

  return 0;
}
