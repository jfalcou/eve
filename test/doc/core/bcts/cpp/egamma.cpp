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
            << "-> egamma(as<wide_ft>())                 = " << eve::egamma(eve::as<wide_ft>())                << std::endl
            << "-> egamma(as(wxf))                       = " << eve::egamma(eve::as(wxf))                      << std::endl
            << "-> upward(egamma)(as<wide_ft>())         = " << eve::upward(eve::egamma)(eve::as<wide_ft>())   << std::endl
            << "-> upward(egamma)(as(wxf))               = " << eve::upward(eve::egamma)(eve::as(wxf))         << std::endl
            << "-> downward(egamma)(as<wide_ft>())       = " << eve::downward(eve::egamma)(eve::as<wide_ft>()) << std::endl
            << "-> downward(egamma)(as(wxf))             = " << eve::downward(eve::egamma)(eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> egamma(as<wide_dt>())           = " << eve::egamma(eve::as<wide_dt>())                << std::endl
            << "-> egamma(as(wxd))                 = " << eve::egamma(eve::as(wxd))                      << std::endl
            << "-> upward(egamma)(as<wide_dt>())   = " << eve::upward(eve::egamma)(eve::as<wide_dt>())   << std::endl
            << "-> upward(egamma)(as(wxd))         = " << eve::upward(eve::egamma)(eve::as(wxd))         << std::endl
            << "-> downward(egamma)(as<wide_dt>()) = " << eve::downward(eve::egamma)(eve::as<wide_dt>()) << std::endl
            << "-> downward(egamma)(as(wxd))       = " << eve::downward(eve::egamma)(eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> egamma(as<float>())             = " << eve::egamma(eve::as(float())) << std::endl
            << "-> egamma(as<xf))                  = " << eve::egamma(eve::as(xf))      << std::endl
            << "-> egamma(as<double>())            = " << eve::egamma(eve::as(double()))<< std::endl
            << "-> egamma(as<xd))                  = " << eve::egamma(eve::as(xd))      << std::endl;

  return 0;
}
