#include <eve/constant/half.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float>;

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::endl
            << "-> half(as<wide_ft>())  = " << eve::half(eve::as<wide_ft>()) << std::endl
            << "-> half(as(wxf))        = " << eve::half(eve::as(wxf))       << std::endl;

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> half(as<float>())         = " << eve::half(eve::as(float())) << std::endl
            << "-> half(as<xf))              = " << eve::half(eve::as(xf)) << std::endl;

  return 0;
}
