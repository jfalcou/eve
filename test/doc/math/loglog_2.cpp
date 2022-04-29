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
            << "-> loglog_2(as<wide_ft>())                 = " << eve::loglog_2(eve::as<wide_ft>())                << std::endl
            << "-> loglog_2(as(wxf))                       = " << eve::loglog_2(eve::as(wxf))                      << std::endl
            << "-> upward(loglog_2)(as<wide_ft>())         = " << eve::upward(eve::loglog_2)(eve::as<wide_ft>())   << std::endl
            << "-> upward(loglog_2)(as(wxf))               = " << eve::upward(eve::loglog_2)(eve::as(wxf))         << std::endl
            << "-> downward(loglog_2)(as<wide_ft>())       = " << eve::downward(eve::loglog_2)(eve::as<wide_ft>()) << std::endl
            << "-> downward(loglog_2)(as(wxf))             = " << eve::downward(eve::loglog_2)(eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> loglog_2(as<wide_dt>())           = " << eve::loglog_2(eve::as<wide_dt>())                << std::endl
            << "-> loglog_2(as(wxd))                 = " << eve::loglog_2(eve::as(wxd))                      << std::endl
            << "-> upward(loglog_2)(as<wide_dt>())   = " << eve::upward(eve::loglog_2)(eve::as<wide_dt>())   << std::endl
            << "-> upward(loglog_2)(as(wxd))         = " << eve::upward(eve::loglog_2)(eve::as(wxd))         << std::endl
            << "-> downward(loglog_2)(as<wide_dt>()) = " << eve::downward(eve::loglog_2)(eve::as<wide_dt>()) << std::endl
            << "-> downward(loglog_2)(as(wxd))       = " << eve::downward(eve::loglog_2)(eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> loglog_2(as<float>())             = " << eve::loglog_2(eve::as(float())) << std::endl
            << "-> loglog_2(as<xf))                  = " << eve::loglog_2(eve::as(xf))      << std::endl
            << "-> loglog_2(as<double>())            = " << eve::loglog_2(eve::as(double()))<< std::endl
            << "-> loglog_2(as<xd))                  = " << eve::loglog_2(eve::as(xd))      << std::endl;

  return 0;
}
