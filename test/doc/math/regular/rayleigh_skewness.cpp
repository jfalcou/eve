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
            << "-> rayleigh_skewness(as<wide_ft>())                 = " << eve::rayleigh_skewness(eve::as<wide_ft>())                << std::endl
            << "-> rayleigh_skewness(as(wxf))                       = " << eve::rayleigh_skewness(eve::as(wxf))                      << std::endl
            << "-> rayleigh_skewness[upward](as<wide_ft>())         = " << eve::rayleigh_skewness[eve::upward](eve::as<wide_ft>())   << std::endl
            << "-> rayleigh_skewness[upward](as(wxf))               = " << eve::rayleigh_skewness[eve::upward](eve::as(wxf))         << std::endl
            << "-> rayleigh_skewness[downward](as<wide_ft>())       = " << eve::rayleigh_skewness[eve::downward](eve::as<wide_ft>()) << std::endl
            << "-> rayleigh_skewness[downward](as(wxf))             = " << eve::rayleigh_skewness[eve::downward](eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> rayleigh_skewness(as<wide_dt>())           = " << eve::rayleigh_skewness(eve::as<wide_dt>())                << std::endl
            << "-> rayleigh_skewness(as(wxd))                 = " << eve::rayleigh_skewness(eve::as(wxd))                      << std::endl
            << "-> rayleigh_skewness[upward](as<wide_dt>())   = " << eve::rayleigh_skewness[eve::upward](eve::as<wide_dt>())   << std::endl
            << "-> rayleigh_skewness[upward](as(wxd))         = " << eve::rayleigh_skewness[eve::upward](eve::as(wxd))         << std::endl
            << "-> rayleigh_skewness[downward](as<wide_dt>()) = " << eve::rayleigh_skewness[eve::downward](eve::as<wide_dt>()) << std::endl
            << "-> rayleigh_skewness[downward](as(wxd))       = " << eve::rayleigh_skewness[eve::downward](eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> rayleigh_skewness(as<float>())             = " << eve::rayleigh_skewness(eve::as(float())) << std::endl
            << "-> rayleigh_skewness(as<xf))                  = " << eve::rayleigh_skewness(eve::as(xf))      << std::endl
            << "-> rayleigh_skewness(as<double>())            = " << eve::rayleigh_skewness(eve::as(double()))<< std::endl
            << "-> rayleigh_skewness(as<xd))                  = " << eve::rayleigh_skewness(eve::as(xd))      << std::endl;

  return 0;
}
