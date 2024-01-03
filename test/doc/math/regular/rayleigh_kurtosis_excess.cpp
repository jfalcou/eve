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
            << "-> rayleigh_kurtosis_excess(as<wide_ft>())                 = " << eve::rayleigh_kurtosis_excess(eve::as<wide_ft>())                << std::endl
            << "-> rayleigh_kurtosis_excess(as(wxf))                       = " << eve::rayleigh_kurtosis_excess(eve::as(wxf))                      << std::endl
            << "-> rayleigh_kurtosis_excess[upward](as<wide_ft>())         = " << eve::rayleigh_kurtosis_excess[eve::upward](eve::as<wide_ft>())   << std::endl
            << "-> rayleigh_kurtosis_excess[upward](as(wxf))               = " << eve::rayleigh_kurtosis_excess[eve::upward](eve::as(wxf))         << std::endl
            << "-> rayleigh_kurtosis_excess[downward](as<wide_ft>())       = " << eve::rayleigh_kurtosis_excess[eve::downward](eve::as<wide_ft>()) << std::endl
            << "-> rayleigh_kurtosis_excess[downward](as(wxf))             = " << eve::rayleigh_kurtosis_excess[eve::downward](eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> rayleigh_kurtosis_excess(as<wide_dt>())           = " << eve::rayleigh_kurtosis_excess(eve::as<wide_dt>())                << std::endl
            << "-> rayleigh_kurtosis_excess(as(wxd))                 = " << eve::rayleigh_kurtosis_excess(eve::as(wxd))                      << std::endl
            << "-> rayleigh_kurtosis_excess[upward](as<wide_dt>())   = " << eve::rayleigh_kurtosis_excess[eve::upward](eve::as<wide_dt>())   << std::endl
            << "-> rayleigh_kurtosis_excess[upward](as(wxd))         = " << eve::rayleigh_kurtosis_excess[eve::upward](eve::as(wxd))         << std::endl
            << "-> rayleigh_kurtosis_excess[downward](as<wide_dt>()) = " << eve::rayleigh_kurtosis_excess[eve::downward](eve::as<wide_dt>()) << std::endl
            << "-> rayleigh_kurtosis_excess[downward](as(wxd))       = " << eve::rayleigh_kurtosis_excess[eve::downward](eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> rayleigh_kurtosis_excess(as<float>())             = " << eve::rayleigh_kurtosis_excess(eve::as(float())) << std::endl
            << "-> rayleigh_kurtosis_excess(as<xf))                  = " << eve::rayleigh_kurtosis_excess(eve::as(xf))      << std::endl
            << "-> rayleigh_kurtosis_excess(as<double>())            = " << eve::rayleigh_kurtosis_excess(eve::as(double()))<< std::endl
            << "-> rayleigh_kurtosis_excess(as<xd))                  = " << eve::rayleigh_kurtosis_excess(eve::as(xd))      << std::endl;

  return 0;
}
