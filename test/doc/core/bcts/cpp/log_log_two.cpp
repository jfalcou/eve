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
            << "-> log_log_two(as<wide_ft>())                 = " << eve::log_log_two(eve::as<wide_ft>())                << std::endl
            << "-> log_log_two(as(wxf))                       = " << eve::log_log_two(eve::as(wxf))                      << std::endl
            << "-> upward(log_log_two)(as<wide_ft>())         = " << eve::upward(eve::log_log_two)(eve::as<wide_ft>())   << std::endl
            << "-> upward(log_log_two)(as(wxf))               = " << eve::upward(eve::log_log_two)(eve::as(wxf))         << std::endl
            << "-> downward(log_log_two)(as<wide_ft>())       = " << eve::downward(eve::log_log_two)(eve::as<wide_ft>()) << std::endl
            << "-> downward(log_log_two)(as(wxf))             = " << eve::downward(eve::log_log_two)(eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> log_log_two(as<wide_dt>())           = " << eve::log_log_two(eve::as<wide_dt>())                << std::endl
            << "-> log_log_two(as(wxd))                 = " << eve::log_log_two(eve::as(wxd))                      << std::endl
            << "-> upward(log_log_two)(as<wide_dt>())   = " << eve::upward(eve::log_log_two)(eve::as<wide_dt>())   << std::endl
            << "-> upward(log_log_two)(as(wxd))         = " << eve::upward(eve::log_log_two)(eve::as(wxd))         << std::endl
            << "-> downward(log_log_two)(as<wide_dt>()) = " << eve::downward(eve::log_log_two)(eve::as<wide_dt>()) << std::endl
            << "-> downward(log_log_two)(as(wxd))       = " << eve::downward(eve::log_log_two)(eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> log_log_two(as<float>())             = " << eve::log_log_two(eve::as(float())) << std::endl
            << "-> log_log_two(as<xf))                  = " << eve::log_log_two(eve::as(xf))      << std::endl
            << "-> log_log_two(as<double>())            = " << eve::log_log_two(eve::as(double()))<< std::endl
            << "-> log_log_two(as<xd))                  = " << eve::log_log_two(eve::as(xd))      << std::endl;

  return 0;
}
