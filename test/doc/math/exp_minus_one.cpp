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
            << "-> exp_minus_one(as<wide_ft>())                 = " << eve::exp_minus_one(eve::as<wide_ft>())                << std::endl
            << "-> exp_minus_one(as(wxf))                       = " << eve::exp_minus_one(eve::as(wxf))                      << std::endl
            << "-> upward(exp_minus_one)(as<wide_ft>())         = " << eve::upward(eve::exp_minus_one)(eve::as<wide_ft>())   << std::endl
            << "-> upward(exp_minus_one)(as(wxf))               = " << eve::upward(eve::exp_minus_one)(eve::as(wxf))         << std::endl
            << "-> downward(exp_minus_one)(as<wide_ft>())       = " << eve::downward(eve::exp_minus_one)(eve::as<wide_ft>()) << std::endl
            << "-> downward(exp_minus_one)(as(wxf))             = " << eve::downward(eve::exp_minus_one)(eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> exp_minus_one(as<wide_dt>())           = " << eve::exp_minus_one(eve::as<wide_dt>())                << std::endl
            << "-> exp_minus_one(as(wxd))                 = " << eve::exp_minus_one(eve::as(wxd))                      << std::endl
            << "-> upward(exp_minus_one)(as<wide_dt>())   = " << eve::upward(eve::exp_minus_one)(eve::as<wide_dt>())   << std::endl
            << "-> upward(exp_minus_one)(as(wxd))         = " << eve::upward(eve::exp_minus_one)(eve::as(wxd))         << std::endl
            << "-> downward(exp_minus_one)(as<wide_dt>()) = " << eve::downward(eve::exp_minus_one)(eve::as<wide_dt>()) << std::endl
            << "-> downward(exp_minus_one)(as(wxd))       = " << eve::downward(eve::exp_minus_one)(eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> exp_minus_one(as<float>())             = " << eve::exp_minus_one(eve::as(float())) << std::endl
            << "-> exp_minus_one(as<xf))                  = " << eve::exp_minus_one(eve::as(xf))      << std::endl
            << "-> exp_minus_one(as<double>())            = " << eve::exp_minus_one(eve::as(double()))<< std::endl
            << "-> exp_minus_one(as<xd))                  = " << eve::exp_minus_one(eve::as(xd))      << std::endl;

  return 0;
}
