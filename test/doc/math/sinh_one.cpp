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
            << "-> sinh_one(as<wide_ft>())                 = " << eve::sinh_one(eve::as<wide_ft>())                << std::endl
            << "-> sinh_one(as(wxf))                       = " << eve::sinh_one(eve::as(wxf))                      << std::endl
            << "-> upward(sinh_one)(as<wide_ft>())         = " << eve::upward(eve::sinh_one)(eve::as<wide_ft>())   << std::endl
            << "-> upward(sinh_one)(as(wxf))               = " << eve::upward(eve::sinh_one)(eve::as(wxf))         << std::endl
            << "-> downward(sinh_one)(as<wide_ft>())       = " << eve::downward(eve::sinh_one)(eve::as<wide_ft>()) << std::endl
            << "-> downward(sinh_one)(as(wxf))             = " << eve::downward(eve::sinh_one)(eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> sinh_one(as<wide_dt>())           = " << eve::sinh_one(eve::as<wide_dt>())                << std::endl
            << "-> sinh_one(as(wxd))                 = " << eve::sinh_one(eve::as(wxd))                      << std::endl
            << "-> upward(sinh_one)(as<wide_dt>())   = " << eve::upward(eve::sinh_one)(eve::as<wide_dt>())   << std::endl
            << "-> upward(sinh_one)(as(wxd))         = " << eve::upward(eve::sinh_one)(eve::as(wxd))         << std::endl
            << "-> downward(sinh_one)(as<wide_dt>()) = " << eve::downward(eve::sinh_one)(eve::as<wide_dt>()) << std::endl
            << "-> downward(sinh_one)(as(wxd))       = " << eve::downward(eve::sinh_one)(eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> sinh_one(as<float>())             = " << eve::sinh_one(eve::as(float())) << std::endl
            << "-> sinh_one(as<xf))                  = " << eve::sinh_one(eve::as(xf))      << std::endl
            << "-> sinh_one(as<double>())            = " << eve::sinh_one(eve::as(double()))<< std::endl
            << "-> sinh_one(as<xd))                  = " << eve::sinh_one(eve::as(xd))      << std::endl;

  return 0;
}
