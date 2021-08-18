#include <eve/constant/sqrt_2o_2.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float>;

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::endl
            << "-> sqrt_2o_2(as<wide_ft>())  = " << eve::sqrt_2o_2(eve::as<wide_ft>()) << std::endl
            << "-> sqrt_2o_2(as(wxf))        = " << eve::sqrt_2o_2(eve::as(wxf))       << std::endl; 

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> sqrt_2o_2(as<float>())         = " << eve::sqrt_2o_2(eve::as(float())) << std::endl
            << "-> sqrt_2o_2(as<xf))              = " << eve::sqrt_2o_2(eve::as(xf)) << std::endl; 

  return 0;
}
