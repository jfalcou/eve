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
            << "-> upward(catalan)(as<wide_ft>())         = " << eve::upward(eve::catalan)(eve::as<wide_ft>())   << std::endl
            << "-> upward(catalan)(as(wxf))               = " << eve::upward(eve::catalan)(eve::as(wxf))         << std::endl
            << "-> downward(catalan)(as<wide_ft>())       = " << eve::downward(eve::catalan)(eve::as<wide_ft>()) << std::endl
            << "-> downward(catalan)(as(wxf))             = " << eve::downward(eve::catalan)(eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> catalan(as<wide_dt>())           = " << eve::catalan(eve::as<wide_dt>())                << std::endl
            << "-> catalan(as(wxd))                 = " << eve::catalan(eve::as(wxd))                      << std::endl
            << "-> upward(catalan)(as<wide_dt>())   = " << eve::upward(eve::catalan)(eve::as<wide_dt>())   << std::endl
            << "-> upward(catalan)(as(wxd))         = " << eve::upward(eve::catalan)(eve::as(wxd))         << std::endl
            << "-> downward(catalan)(as<wide_dt>()) = " << eve::downward(eve::catalan)(eve::as<wide_dt>()) << std::endl
            << "-> downward(catalan)(as(wxd))       = " << eve::downward(eve::catalan)(eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> catalan(as<float>())             = " << eve::catalan(eve::as(float())) << std::endl
            << "-> catalan(as<xf))                  = " << eve::catalan(eve::as(xf))      << std::endl
            << "-> catalan(as<double>())            = " << eve::catalan(eve::as(double()))<< std::endl
            << "-> catalan(as<xd))                  = " << eve::catalan(eve::as(xd))      << std::endl;

  return 0;
}
