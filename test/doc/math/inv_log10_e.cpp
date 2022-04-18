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
            << "-> inv_log10_e(as<wide_ft>())                 = " << eve::inv_log10_e(eve::as<wide_ft>())                << std::endl
            << "-> inv_log10_e(as(wxf))                       = " << eve::inv_log10_e(eve::as(wxf))                      << std::endl
            << "-> upward(inv_log10_e)(as<wide_ft>())         = " << eve::upward(eve::inv_log10_e)(eve::as<wide_ft>())   << std::endl
            << "-> upward(inv_log10_e)(as(wxf))               = " << eve::upward(eve::inv_log10_e)(eve::as(wxf))         << std::endl
            << "-> downward(inv_log10_e)(as<wide_ft>())       = " << eve::downward(eve::inv_log10_e)(eve::as<wide_ft>()) << std::endl
            << "-> downward(inv_log10_e)(as(wxf))             = " << eve::downward(eve::inv_log10_e)(eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> inv_log10_e(as<wide_dt>())           = " << eve::inv_log10_e(eve::as<wide_dt>())                << std::endl
            << "-> inv_log10_e(as(wxd))                 = " << eve::inv_log10_e(eve::as(wxd))                      << std::endl
            << "-> upward(inv_log10_e)(as<wide_dt>())   = " << eve::upward(eve::inv_log10_e)(eve::as<wide_dt>())   << std::endl
            << "-> upward(inv_log10_e)(as(wxd))         = " << eve::upward(eve::inv_log10_e)(eve::as(wxd))         << std::endl
            << "-> downward(inv_log10_e)(as<wide_dt>()) = " << eve::downward(eve::inv_log10_e)(eve::as<wide_dt>()) << std::endl
            << "-> downward(inv_log10_e)(as(wxd))       = " << eve::downward(eve::inv_log10_e)(eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> inv_log10_e(as<float>())             = " << eve::inv_log10_e(eve::as(float())) << std::endl
            << "-> inv_log10_e(as<xf))                  = " << eve::inv_log10_e(eve::as(xf))      << std::endl
            << "-> inv_log10_e(as<double>())            = " << eve::inv_log10_e(eve::as(double()))<< std::endl
            << "-> inv_log10_e(as<xd))                  = " << eve::inv_log10_e(eve::as(xd))      << std::endl;

  return 0;
}
