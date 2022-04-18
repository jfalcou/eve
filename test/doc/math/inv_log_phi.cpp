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
            << "-> inv_log_phi(as<wide_ft>())                 = " << eve::inv_log_phi(eve::as<wide_ft>())                << std::endl
            << "-> inv_log_phi(as(wxf))                       = " << eve::inv_log_phi(eve::as(wxf))                      << std::endl
            << "-> upward(inv_log_phi)(as<wide_ft>())         = " << eve::upward(eve::inv_log_phi)(eve::as<wide_ft>())   << std::endl
            << "-> upward(inv_log_phi)(as(wxf))               = " << eve::upward(eve::inv_log_phi)(eve::as(wxf))         << std::endl
            << "-> downward(inv_log_phi)(as<wide_ft>())       = " << eve::downward(eve::inv_log_phi)(eve::as<wide_ft>()) << std::endl
            << "-> downward(inv_log_phi)(as(wxf))             = " << eve::downward(eve::inv_log_phi)(eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> inv_log_phi(as<wide_dt>())           = " << eve::inv_log_phi(eve::as<wide_dt>())                << std::endl
            << "-> inv_log_phi(as(wxd))                 = " << eve::inv_log_phi(eve::as(wxd))                      << std::endl
            << "-> upward(inv_log_phi)(as<wide_dt>())   = " << eve::upward(eve::inv_log_phi)(eve::as<wide_dt>())   << std::endl
            << "-> upward(inv_log_phi)(as(wxd))         = " << eve::upward(eve::inv_log_phi)(eve::as(wxd))         << std::endl
            << "-> downward(inv_log_phi)(as<wide_dt>()) = " << eve::downward(eve::inv_log_phi)(eve::as<wide_dt>()) << std::endl
            << "-> downward(inv_log_phi)(as(wxd))       = " << eve::downward(eve::inv_log_phi)(eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> inv_log_phi(as<float>())             = " << eve::inv_log_phi(eve::as(float())) << std::endl
            << "-> inv_log_phi(as<xf))                  = " << eve::inv_log_phi(eve::as(xf))      << std::endl
            << "-> inv_log_phi(as<double>())            = " << eve::inv_log_phi(eve::as(double()))<< std::endl
            << "-> inv_log_phi(as<xd))                  = " << eve::inv_log_phi(eve::as(xd))      << std::endl;

  return 0;
}
