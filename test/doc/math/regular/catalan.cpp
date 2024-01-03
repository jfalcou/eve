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
            << "-> catalan(as<wide_ft>())                 = " << eve::catalan(eve::as<wide_ft>())                << std::endl
            << "-> catalan(as(wxf))                       = " << eve::catalan(eve::as(wxf))                      << std::endl
            << "-> catalan[upward](as<wide_ft>())         = " << eve::catalan[eve::upward](eve::as<wide_ft>())   << std::endl
            << "-> catalan[upward](as(wxf))               = " << eve::catalan[eve::upward](eve::as(wxf))         << std::endl
            << "-> catalan[downward](as<wide_ft>())       = " << eve::catalan[eve::downward](eve::as<wide_ft>()) << std::endl
            << "-> catalan[downward](as(wxf))             = " << eve::catalan[eve::downward](eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> catalan(as<wide_dt>())           = " << eve::catalan(eve::as<wide_dt>())                << std::endl
            << "-> catalan(as(wxd))                 = " << eve::catalan(eve::as(wxd))                      << std::endl
            << "-> catalan[upward](as<wide_dt>())   = " << eve::catalan[eve::upward](eve::as<wide_dt>())   << std::endl
            << "-> catalan[upward](as(wxd))         = " << eve::catalan[eve::upward](eve::as(wxd))         << std::endl
            << "-> catalan[downward](as<wide_dt>()) = " << eve::catalan[eve::downward](eve::as<wide_dt>()) << std::endl
            << "-> catalan[downward](as(wxd))       = " << eve::catalan[eve::downward](eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> catalan(as<float>())             = " << eve::catalan(eve::as(float())) << std::endl
            << "-> catalan(as<xf))                  = " << eve::catalan(eve::as(xf))      << std::endl
            << "-> catalan(as<double>())            = " << eve::catalan(eve::as(double()))<< std::endl
            << "-> catalan(as<xd))                  = " << eve::catalan(eve::as(xd))      << std::endl;

  return 0;
}
