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
            << "-> egamma_sqr(as<wide_ft>())                 = " << eve::egamma_sqr(eve::as<wide_ft>())                << std::endl
            << "-> egamma_sqr(as(wxf))                       = " << eve::egamma_sqr(eve::as(wxf))                      << std::endl
            << "-> upward(egamma_sqr)(as<wide_ft>())         = " << eve::upward(eve::egamma_sqr)(eve::as<wide_ft>())   << std::endl
            << "-> upward(egamma_sqr)(as(wxf))               = " << eve::upward(eve::egamma_sqr)(eve::as(wxf))         << std::endl
            << "-> downward(egamma_sqr)(as<wide_ft>())       = " << eve::downward(eve::egamma_sqr)(eve::as<wide_ft>()) << std::endl
            << "-> downward(egamma_sqr)(as(wxf))             = " << eve::downward(eve::egamma_sqr)(eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> egamma_sqr(as<wide_dt>())           = " << eve::egamma_sqr(eve::as<wide_dt>())                << std::endl
            << "-> egamma_sqr(as(wxd))                 = " << eve::egamma_sqr(eve::as(wxd))                      << std::endl
            << "-> upward(egamma_sqr)(as<wide_dt>())   = " << eve::upward(eve::egamma_sqr)(eve::as<wide_dt>())   << std::endl
            << "-> upward(egamma_sqr)(as(wxd))         = " << eve::upward(eve::egamma_sqr)(eve::as(wxd))         << std::endl
            << "-> downward(egamma_sqr)(as<wide_dt>()) = " << eve::downward(eve::egamma_sqr)(eve::as<wide_dt>()) << std::endl
            << "-> downward(egamma_sqr)(as(wxd))       = " << eve::downward(eve::egamma_sqr)(eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> egamma_sqr(as<float>())             = " << eve::egamma_sqr(eve::as(float())) << std::endl
            << "-> egamma_sqr(as<xf))                  = " << eve::egamma_sqr(eve::as(xf))      << std::endl
            << "-> egamma_sqr(as<double>())            = " << eve::egamma_sqr(eve::as(double()))<< std::endl
            << "-> egamma_sqr(as<xd))                  = " << eve::egamma_sqr(eve::as(xd))      << std::endl;

  return 0;
}
