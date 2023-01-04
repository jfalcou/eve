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
            << "-> sin_1(as<wide_ft>())                 = " << eve::sin_1(eve::as<wide_ft>())                << std::endl
            << "-> sin_1(as(wxf))                       = " << eve::sin_1(eve::as(wxf))                      << std::endl
            << "-> upward(sin_1)(as<wide_ft>())         = " << eve::upward(eve::sin_1)(eve::as<wide_ft>())   << std::endl
            << "-> upward(sin_1)(as(wxf))               = " << eve::upward(eve::sin_1)(eve::as(wxf))         << std::endl
            << "-> downward(sin_1)(as<wide_ft>())       = " << eve::downward(eve::sin_1)(eve::as<wide_ft>()) << std::endl
            << "-> downward(sin_1)(as(wxf))             = " << eve::downward(eve::sin_1)(eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> sin_1(as<wide_dt>())           = " << eve::sin_1(eve::as<wide_dt>())                << std::endl
            << "-> sin_1(as(wxd))                 = " << eve::sin_1(eve::as(wxd))                      << std::endl
            << "-> upward(sin_1)(as<wide_dt>())   = " << eve::upward(eve::sin_1)(eve::as<wide_dt>())   << std::endl
            << "-> upward(sin_1)(as(wxd))         = " << eve::upward(eve::sin_1)(eve::as(wxd))         << std::endl
            << "-> downward(sin_1)(as<wide_dt>()) = " << eve::downward(eve::sin_1)(eve::as<wide_dt>()) << std::endl
            << "-> downward(sin_1)(as(wxd))       = " << eve::downward(eve::sin_1)(eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> sin_1(as<float>())             = " << eve::sin_1(eve::as(float())) << std::endl
            << "-> sin_1(as<xf))                  = " << eve::sin_1(eve::as(xf))      << std::endl
            << "-> sin_1(as<double>())            = " << eve::sin_1(eve::as(double()))<< std::endl
            << "-> sin_1(as<xd))                  = " << eve::sin_1(eve::as(xd))      << std::endl;

  return 0;
}
