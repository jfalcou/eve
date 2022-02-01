#include <eve/module/arithmetic/constant/nbmantissabits.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float>;

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::endl
            << "-> nbmantissabits(as<wide_ft>())  = " << eve::nbmantissabits(eve::as<wide_ft>()) << std::endl
            << "-> nbmantissabits(as(wxf))        = " << eve::nbmantissabits(eve::as(wxf))       << std::endl;

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> nbmantissabits(as<float>())         = " << eve::nbmantissabits(eve::as(float())) << std::endl
            << "-> nbmantissabits(as<xf))              = " << eve::nbmantissabits(eve::as(xf)) << std::endl;

  return 0;
}
