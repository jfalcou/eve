#include <eve/module/math/constant/invsqrt_2.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float>;

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::endl
            << "-> invsqrt_2(as<wide_ft>())  = " << eve::invsqrt_2(eve::as<wide_ft>()) << std::endl
            << "-> invsqrt_2(as(wxf))        = " << eve::invsqrt_2(eve::as(wxf))       << std::endl;

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> invsqrt_2(as<float>())         = " << eve::invsqrt_2(eve::as(float())) << std::endl
            << "-> invsqrt_2(as<xf))              = " << eve::invsqrt_2(eve::as(xf)) << std::endl;

  return 0;
}
