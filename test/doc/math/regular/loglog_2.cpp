#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;
using wide_dt = eve::wide<double>;

template<typename T>
consteval auto constexpr_loglog_2() { return eve::loglog_2(eve::as<T>{}); }

int main()
{
  wide_ft wxf;
  wide_dt wxd;

  std::cout << "---- simd"  << std::setprecision(9) << std::endl
            << "-> loglog_2(as<wide_ft>())                 = " << eve::loglog_2(eve::as<wide_ft>())                << std::endl
            << "-> loglog_2(as(wxf))                       = " << eve::loglog_2(eve::as(wxf))                      << std::endl
            << "-> loglog_2[upward](as<wide_ft>())         = " << eve::loglog_2[eve::upward](eve::as<wide_ft>())   << std::endl
            << "-> loglog_2[upward](as(wxf))               = " << eve::loglog_2[eve::upward](eve::as(wxf))         << std::endl
            << "-> loglog_2[downward](as<wide_ft>())       = " << eve::loglog_2[eve::downward](eve::as<wide_ft>()) << std::endl
            << "-> loglog_2[downward](as(wxf))             = " << eve::loglog_2[eve::downward](eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> loglog_2(as<wide_dt>())           = " << eve::loglog_2(eve::as<wide_dt>())                << std::endl
            << "-> loglog_2(as(wxd))                 = " << eve::loglog_2(eve::as(wxd))                      << std::endl
            << "-> loglog_2[upward](as<wide_dt>())   = " << eve::loglog_2[eve::upward](eve::as<wide_dt>())   << std::endl
            << "-> loglog_2[upward](as(wxd))         = " << eve::loglog_2[eve::upward](eve::as(wxd))         << std::endl
            << "-> loglog_2[downward](as<wide_dt>()) = " << eve::loglog_2[eve::downward](eve::as<wide_dt>()) << std::endl
            << "-> loglog_2[downward](as(wxd))       = " << eve::loglog_2[eve::downward](eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> loglog_2(as<float>())             = " << eve::loglog_2(eve::as(float())) << std::endl
            << "-> loglog_2(as<xf))                  = " << eve::loglog_2(eve::as(xf))      << std::endl
            << "-> loglog_2(as<double>())            = " << eve::loglog_2(eve::as(double()))<< std::endl
            << "-> loglog_2(as<xd))                  = " << eve::loglog_2(eve::as(xd))      << std::endl;


  std::cout << "-> constexpr loglog_2            = " << constexpr_loglog_2<float>() << std::endl;

  return 0;
}
