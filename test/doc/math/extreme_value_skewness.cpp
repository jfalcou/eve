#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;
using wide_dt = eve::wide<double>;

int main()
{
  wide_ft wxf;
  wide_dt wxd;

  std::cout << "---- simd"  << std::setprecision(9) << std::endl
            << "-> extreme_value_skewness(as<wide_ft>())                 = " << eve::extreme_value_skewness(eve::as<wide_ft>())                << std::endl
            << "-> extreme_value_skewness(as(wxf))                       = " << eve::extreme_value_skewness(eve::as(wxf))                      << std::endl
            << "-> upward(extreme_value_skewness)(as<wide_ft>())         = " << eve::upward(eve::extreme_value_skewness)(eve::as<wide_ft>())   << std::endl
            << "-> upward(extreme_value_skewness)(as(wxf))               = " << eve::upward(eve::extreme_value_skewness)(eve::as(wxf))         << std::endl
            << "-> downward(extreme_value_skewness)(as<wide_ft>())       = " << eve::downward(eve::extreme_value_skewness)(eve::as<wide_ft>()) << std::endl
            << "-> downward(extreme_value_skewness)(as(wxf))             = " << eve::downward(eve::extreme_value_skewness)(eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> extreme_value_skewness(as<wide_dt>())           = " << eve::extreme_value_skewness(eve::as<wide_dt>())                << std::endl
            << "-> extreme_value_skewness(as(wxd))                 = " << eve::extreme_value_skewness(eve::as(wxd))                      << std::endl
            << "-> upward(extreme_value_skewness)(as<wide_dt>())   = " << eve::upward(eve::extreme_value_skewness)(eve::as<wide_dt>())   << std::endl
            << "-> upward(extreme_value_skewness)(as(wxd))         = " << eve::upward(eve::extreme_value_skewness)(eve::as(wxd))         << std::endl
            << "-> downward(extreme_value_skewness)(as<wide_dt>()) = " << eve::downward(eve::extreme_value_skewness)(eve::as<wide_dt>()) << std::endl
            << "-> downward(extreme_value_skewness)(as(wxd))       = " << eve::downward(eve::extreme_value_skewness)(eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> extreme_value_skewness(as<float>())             = " << eve::extreme_value_skewness(eve::as(float())) << std::endl
            << "-> extreme_value_skewness(as<xf))                  = " << eve::extreme_value_skewness(eve::as(xf))      << std::endl
            << "-> extreme_value_skewness(as<double>())            = " << eve::extreme_value_skewness(eve::as(double()))<< std::endl
            << "-> extreme_value_skewness(as<xd))                  = " << eve::extreme_value_skewness(eve::as(xd))      << std::endl;

  return 0;
}
