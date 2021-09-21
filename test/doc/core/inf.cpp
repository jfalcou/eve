#include <eve/constant/inf.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float>;

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::endl
            << "-> inf(as<wide_ft>())  = " << eve::inf(eve::as<wide_ft>()) << std::endl
            << "-> inf(as(wxf))        = " << eve::inf(eve::as(wxf))       << std::endl;

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> inf(as<float>())         = " << eve::inf(eve::as(float())) << std::endl
            << "-> inf(as<xf))              = " << eve::inf(eve::as(xf)) << std::endl;

  return 0;
}
