#include <eve/constant/oneosqrteps.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float>;

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::endl
            << "-> oneosqrteps(as<wide_ft>())  = " << eve::oneosqrteps(eve::as<wide_ft>()) << std::endl
            << "-> oneosqrteps(as(wxf))        = " << eve::oneosqrteps(eve::as(wxf))       << std::endl;

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> oneosqrteps(as<float>())         = " << eve::oneosqrteps(eve::as(float())) << std::endl
            << "-> oneosqrteps(as<xf))              = " << eve::oneosqrteps(eve::as(xf)) << std::endl;

  return 0;
}
