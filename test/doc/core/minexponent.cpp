#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float>;

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::endl
            << "-> minexponent(as<wide_ft>())  = " << eve::minexponent(eve::as<wide_ft>()) << std::endl
            << "-> minexponent(as(wxf))        = " << eve::minexponent(eve::as(wxf))       << std::endl;

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> minexponent(as<float>())         = " << eve::minexponent(eve::as(float())) << std::endl
            << "-> minexponent(as<xf))              = " << eve::minexponent(eve::as(xf)) << std::endl;

  return 0;
}
