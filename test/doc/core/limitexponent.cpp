#include <eve/constant/limitexponent.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float>;

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::endl
            << "-> limitexponent(as<wide_ft>())  = " << eve::limitexponent(eve::as<wide_ft>()) << std::endl
            << "-> limitexponent(as(wxf))        = " << eve::limitexponent(eve::as(wxf))       << std::endl;

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> limitexponent(as<float>())         = " << eve::limitexponent(eve::as(float())) << std::endl
            << "-> limitexponent(as<xf))              = " << eve::limitexponent(eve::as(xf)) << std::endl;

  return 0;
}
