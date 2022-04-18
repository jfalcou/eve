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
            << "-> sin_one(as<wide_ft>())                 = " << eve::sin_one(eve::as<wide_ft>())                << std::endl
            << "-> sin_one(as(wxf))                       = " << eve::sin_one(eve::as(wxf))                      << std::endl
            << "-> upward(sin_one)(as<wide_ft>())         = " << eve::upward(eve::sin_one)(eve::as<wide_ft>())   << std::endl
            << "-> upward(sin_one)(as(wxf))               = " << eve::upward(eve::sin_one)(eve::as(wxf))         << std::endl
            << "-> downward(sin_one)(as<wide_ft>())       = " << eve::downward(eve::sin_one)(eve::as<wide_ft>()) << std::endl
            << "-> downward(sin_one)(as(wxf))             = " << eve::downward(eve::sin_one)(eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> sin_one(as<wide_dt>())           = " << eve::sin_one(eve::as<wide_dt>())                << std::endl
            << "-> sin_one(as(wxd))                 = " << eve::sin_one(eve::as(wxd))                      << std::endl
            << "-> upward(sin_one)(as<wide_dt>())   = " << eve::upward(eve::sin_one)(eve::as<wide_dt>())   << std::endl
            << "-> upward(sin_one)(as(wxd))         = " << eve::upward(eve::sin_one)(eve::as(wxd))         << std::endl
            << "-> downward(sin_one)(as<wide_dt>()) = " << eve::downward(eve::sin_one)(eve::as<wide_dt>()) << std::endl
            << "-> downward(sin_one)(as(wxd))       = " << eve::downward(eve::sin_one)(eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> sin_one(as<float>())             = " << eve::sin_one(eve::as(float())) << std::endl
            << "-> sin_one(as<xf))                  = " << eve::sin_one(eve::as(xf))      << std::endl
            << "-> sin_one(as<double>())            = " << eve::sin_one(eve::as(double()))<< std::endl
            << "-> sin_one(as<xd))                  = " << eve::sin_one(eve::as(xd))      << std::endl;

  return 0;
}
