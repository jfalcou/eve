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
            << "-> quarter(as<wide_ft>())                 = " << eve::quarter(eve::as<wide_ft>())                << std::endl
            << "-> quarter(as(wxf))                       = " << eve::quarter(eve::as(wxf))                      << std::endl
            << "-> upward(quarter)(as<wide_ft>())         = " << eve::upward(eve::quarter)(eve::as<wide_ft>())   << std::endl
            << "-> upward(quarter)(as(wxf))               = " << eve::upward(eve::quarter)(eve::as(wxf))         << std::endl
            << "-> downward(quarter)(as<wide_ft>())       = " << eve::downward(eve::quarter)(eve::as<wide_ft>()) << std::endl
            << "-> downward(quarter)(as(wxf))             = " << eve::downward(eve::quarter)(eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> quarter(as<wide_dt>())           = " << eve::quarter(eve::as<wide_dt>())                << std::endl
            << "-> quarter(as(wxd))                 = " << eve::quarter(eve::as(wxd))                      << std::endl
            << "-> upward(quarter)(as<wide_dt>())   = " << eve::upward(eve::quarter)(eve::as<wide_dt>())   << std::endl
            << "-> upward(quarter)(as(wxd))         = " << eve::upward(eve::quarter)(eve::as(wxd))         << std::endl
            << "-> downward(quarter)(as<wide_dt>()) = " << eve::downward(eve::quarter)(eve::as<wide_dt>()) << std::endl
            << "-> downward(quarter)(as(wxd))       = " << eve::downward(eve::quarter)(eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> quarter(as<float>())             = " << eve::quarter(eve::as(float())) << std::endl
            << "-> quarter(as<xf))                  = " << eve::quarter(eve::as(xf))      << std::endl
            << "-> quarter(as<double>())            = " << eve::quarter(eve::as(double()))<< std::endl
            << "-> quarter(as<xd))                  = " << eve::quarter(eve::as(xd))      << std::endl;

  return 0;
}
