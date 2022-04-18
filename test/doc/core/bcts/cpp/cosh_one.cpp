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
            << "-> cosh_one(as<wide_ft>())                 = " << eve::cosh_one(eve::as<wide_ft>())                << std::endl
            << "-> cosh_one(as(wxf))                       = " << eve::cosh_one(eve::as(wxf))                      << std::endl
            << "-> upward(cosh_one)(as<wide_ft>())         = " << eve::upward(eve::cosh_one)(eve::as<wide_ft>())   << std::endl
            << "-> upward(cosh_one)(as(wxf))               = " << eve::upward(eve::cosh_one)(eve::as(wxf))         << std::endl
            << "-> downward(cosh_one)(as<wide_ft>())       = " << eve::downward(eve::cosh_one)(eve::as<wide_ft>()) << std::endl
            << "-> downward(cosh_one)(as(wxf))             = " << eve::downward(eve::cosh_one)(eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> cosh_one(as<wide_dt>())           = " << eve::cosh_one(eve::as<wide_dt>())                << std::endl
            << "-> cosh_one(as(wxd))                 = " << eve::cosh_one(eve::as(wxd))                      << std::endl
            << "-> upward(cosh_one)(as<wide_dt>())   = " << eve::upward(eve::cosh_one)(eve::as<wide_dt>())   << std::endl
            << "-> upward(cosh_one)(as(wxd))         = " << eve::upward(eve::cosh_one)(eve::as(wxd))         << std::endl
            << "-> downward(cosh_one)(as<wide_dt>()) = " << eve::downward(eve::cosh_one)(eve::as<wide_dt>()) << std::endl
            << "-> downward(cosh_one)(as(wxd))       = " << eve::downward(eve::cosh_one)(eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> cosh_one(as<float>())             = " << eve::cosh_one(eve::as(float())) << std::endl
            << "-> cosh_one(as<xf))                  = " << eve::cosh_one(eve::as(xf))      << std::endl
            << "-> cosh_one(as<double>())            = " << eve::cosh_one(eve::as(double()))<< std::endl
            << "-> cosh_one(as<xd))                  = " << eve::cosh_one(eve::as(xd))      << std::endl;

  return 0;
}
