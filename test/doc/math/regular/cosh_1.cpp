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
            << "-> cosh_1(as<wide_ft>())                 = " << eve::cosh_1(eve::as<wide_ft>())                << std::endl
            << "-> cosh_1(as(wxf))                       = " << eve::cosh_1(eve::as(wxf))                      << std::endl
            << "-> upward(cosh_1)(as<wide_ft>())         = " << eve::upward(eve::cosh_1)(eve::as<wide_ft>())   << std::endl
            << "-> upward(cosh_1)(as(wxf))               = " << eve::upward(eve::cosh_1)(eve::as(wxf))         << std::endl
            << "-> downward(cosh_1)(as<wide_ft>())       = " << eve::downward(eve::cosh_1)(eve::as<wide_ft>()) << std::endl
            << "-> downward(cosh_1)(as(wxf))             = " << eve::downward(eve::cosh_1)(eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> cosh_1(as<wide_dt>())           = " << eve::cosh_1(eve::as<wide_dt>())                << std::endl
            << "-> cosh_1(as(wxd))                 = " << eve::cosh_1(eve::as(wxd))                      << std::endl
            << "-> upward(cosh_1)(as<wide_dt>())   = " << eve::upward(eve::cosh_1)(eve::as<wide_dt>())   << std::endl
            << "-> upward(cosh_1)(as(wxd))         = " << eve::upward(eve::cosh_1)(eve::as(wxd))         << std::endl
            << "-> downward(cosh_1)(as<wide_dt>()) = " << eve::downward(eve::cosh_1)(eve::as<wide_dt>()) << std::endl
            << "-> downward(cosh_1)(as(wxd))       = " << eve::downward(eve::cosh_1)(eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> cosh_1(as<float>())             = " << eve::cosh_1(eve::as(float())) << std::endl
            << "-> cosh_1(as<xf))                  = " << eve::cosh_1(eve::as(xf))      << std::endl
            << "-> cosh_1(as<double>())            = " << eve::cosh_1(eve::as(double()))<< std::endl
            << "-> cosh_1(as<xd))                  = " << eve::cosh_1(eve::as(xd))      << std::endl;

  return 0;
}
