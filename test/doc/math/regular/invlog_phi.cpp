#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;
using wide_dt = eve::wide<double>;

template<typename T>
consteval auto constexpr_invlog_phi() { return eve::invlog_phi(eve::as<T>{}); }

int main()
{
  wide_ft wxf;
  wide_dt wxd;

  std::cout << "---- simd"  << std::setprecision(9) << std::endl
            << "-> invlog_phi(as<wide_ft>())                 = " << eve::invlog_phi(eve::as<wide_ft>())                << std::endl
            << "-> invlog_phi(as(wxf))                       = " << eve::invlog_phi(eve::as(wxf))                      << std::endl
            << "-> invlog_phi[upward](as<wide_ft>())         = " << eve::invlog_phi[eve::upward](eve::as<wide_ft>())   << std::endl
            << "-> invlog_phi[upward](as(wxf))               = " << eve::invlog_phi[eve::upward](eve::as(wxf))         << std::endl
            << "-> invlog_phi[downward](as<wide_ft>())       = " << eve::invlog_phi[eve::downward](eve::as<wide_ft>()) << std::endl
            << "-> invlog_phi[downward](as(wxf))             = " << eve::invlog_phi[eve::downward](eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> invlog_phi(as<wide_dt>())           = " << eve::invlog_phi(eve::as<wide_dt>())                << std::endl
            << "-> invlog_phi(as(wxd))                 = " << eve::invlog_phi(eve::as(wxd))                      << std::endl
            << "-> invlog_phi[upward](as<wide_dt>())   = " << eve::invlog_phi[eve::upward](eve::as<wide_dt>())   << std::endl
            << "-> invlog_phi[upward](as(wxd))         = " << eve::invlog_phi[eve::upward](eve::as(wxd))         << std::endl
            << "-> invlog_phi[downward](as<wide_dt>()) = " << eve::invlog_phi[eve::downward](eve::as<wide_dt>()) << std::endl
            << "-> invlog_phi[downward](as(wxd))       = " << eve::invlog_phi[eve::downward](eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> invlog_phi(as<float>())             = " << eve::invlog_phi(eve::as(float())) << std::endl
            << "-> invlog_phi(as<xf))                  = " << eve::invlog_phi(eve::as(xf))      << std::endl
            << "-> invlog_phi(as<double>())            = " << eve::invlog_phi(eve::as(double()))<< std::endl
            << "-> invlog_phi(as<xd))                  = " << eve::invlog_phi(eve::as(xd))      << std::endl;


  std::cout << "-> constexpr invlog_phi            = " << constexpr_invlog_phi<float>() << std::endl;

  return 0;
}
