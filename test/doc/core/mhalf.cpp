#include <eve/constant/mhalf.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float>;

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::endl
            << "-> mhalf(as<wide_ft>())  = " << eve::mhalf(eve::as<wide_ft>()) << std::endl
            << "-> mhalf(as(wxf))        = " << eve::mhalf(eve::as(wxf))       << std::endl;

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> mhalf(as<float>())         = " << eve::mhalf(eve::as(float())) << std::endl
            << "-> mhalf(as<xf))              = " << eve::mhalf(eve::as(xf)) << std::endl;

  return 0;
}
