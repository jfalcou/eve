#include <eve/constant/minf.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float>;

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::endl
            << "-> minf(as<wide_ft>())  = " << eve::minf(eve::as<wide_ft>()) << std::endl
            << "-> minf(as(wxf))        = " << eve::minf(eve::as(wxf))       << std::endl;

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> minf(as<float>())         = " << eve::minf(eve::as(float())) << std::endl
            << "-> minf(as<xf))              = " << eve::minf(eve::as(xf)) << std::endl;

  return 0;
}
