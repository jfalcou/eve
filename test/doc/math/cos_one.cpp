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
            << "-> cos_one(as<wide_ft>())                 = " << eve::cos_one(eve::as<wide_ft>())                << std::endl
            << "-> cos_one(as(wxf))                       = " << eve::cos_one(eve::as(wxf))                      << std::endl
            << "-> upward(cos_one)(as<wide_ft>())         = " << eve::upward(eve::cos_one)(eve::as<wide_ft>())   << std::endl
            << "-> upward(cos_one)(as(wxf))               = " << eve::upward(eve::cos_one)(eve::as(wxf))         << std::endl
            << "-> downward(cos_one)(as<wide_ft>())       = " << eve::downward(eve::cos_one)(eve::as<wide_ft>()) << std::endl
            << "-> downward(cos_one)(as(wxf))             = " << eve::downward(eve::cos_one)(eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> cos_one(as<wide_dt>())           = " << eve::cos_one(eve::as<wide_dt>())                << std::endl
            << "-> cos_one(as(wxd))                 = " << eve::cos_one(eve::as(wxd))                      << std::endl
            << "-> upward(cos_one)(as<wide_dt>())   = " << eve::upward(eve::cos_one)(eve::as<wide_dt>())   << std::endl
            << "-> upward(cos_one)(as(wxd))         = " << eve::upward(eve::cos_one)(eve::as(wxd))         << std::endl
            << "-> downward(cos_one)(as<wide_dt>()) = " << eve::downward(eve::cos_one)(eve::as<wide_dt>()) << std::endl
            << "-> downward(cos_one)(as(wxd))       = " << eve::downward(eve::cos_one)(eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> cos_one(as<float>())             = " << eve::cos_one(eve::as(float())) << std::endl
            << "-> cos_one(as<xf))                  = " << eve::cos_one(eve::as(xf))      << std::endl
            << "-> cos_one(as<double>())            = " << eve::cos_one(eve::as(double()))<< std::endl
            << "-> cos_one(as<xd))                  = " << eve::cos_one(eve::as(xd))      << std::endl;

  return 0;
}
