#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::setprecision(9) << std::endl
            << "-> phi(as<wide_ft>())       = " << eve::phi(eve::as<wide_ft>())            << std::endl
            << "-> phi(as(wxf))             = " << eve::phi(eve::as(wxf))                  << std::endl;

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> phi(as<float>())         = " << eve::phi(eve::as(float())) << std::endl
            << "-> phi(as<xf))              = " << eve::phi(eve::as(xf))      << std::endl;

  return 0;
}
