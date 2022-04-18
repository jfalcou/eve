#include <eve/module/core.hpp>
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
            << "-> log_phi(as<wide_ft>())                 = " << eve::log_phi(eve::as<wide_ft>())                << std::endl
            << "-> log_phi(as(wxf))                       = " << eve::log_phi(eve::as(wxf))                      << std::endl
            << "-> upward(log_phi)(as<wide_ft>())         = " << eve::upward(eve::log_phi)(eve::as<wide_ft>())   << std::endl
            << "-> upward(log_phi)(as(wxf))               = " << eve::upward(eve::log_phi)(eve::as(wxf))         << std::endl
            << "-> downward(log_phi)(as<wide_ft>())       = " << eve::downward(eve::log_phi)(eve::as<wide_ft>()) << std::endl
            << "-> downward(log_phi)(as(wxf))             = " << eve::downward(eve::log_phi)(eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> log_phi(as<wide_dt>())           = " << eve::log_phi(eve::as<wide_dt>())                << std::endl
            << "-> log_phi(as(wxd))                 = " << eve::log_phi(eve::as(wxd))                      << std::endl
            << "-> upward(log_phi)(as<wide_dt>())   = " << eve::upward(eve::log_phi)(eve::as<wide_dt>())   << std::endl
            << "-> upward(log_phi)(as(wxd))         = " << eve::upward(eve::log_phi)(eve::as(wxd))         << std::endl
            << "-> downward(log_phi)(as<wide_dt>()) = " << eve::downward(eve::log_phi)(eve::as<wide_dt>()) << std::endl
            << "-> downward(log_phi)(as(wxd))       = " << eve::downward(eve::log_phi)(eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> log_phi(as<float>())             = " << eve::log_phi(eve::as(float())) << std::endl
            << "-> log_phi(as<xf))                  = " << eve::log_phi(eve::as(xf))      << std::endl
            << "-> log_phi(as<double>())            = " << eve::log_phi(eve::as(double()))<< std::endl
            << "-> log_phi(as<xd))                  = " << eve::log_phi(eve::as(xd))      << std::endl;

  return 0;
}
