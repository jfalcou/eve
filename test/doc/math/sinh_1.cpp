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
            << "-> sinh_1(as<wide_ft>())                 = " << eve::sinh_1(eve::as<wide_ft>())                << std::endl
            << "-> sinh_1(as(wxf))                       = " << eve::sinh_1(eve::as(wxf))                      << std::endl
            << "-> upward(sinh_1)(as<wide_ft>())         = " << eve::upward(eve::sinh_1)(eve::as<wide_ft>())   << std::endl
            << "-> upward(sinh_1)(as(wxf))               = " << eve::upward(eve::sinh_1)(eve::as(wxf))         << std::endl
            << "-> downward(sinh_1)(as<wide_ft>())       = " << eve::downward(eve::sinh_1)(eve::as<wide_ft>()) << std::endl
            << "-> downward(sinh_1)(as(wxf))             = " << eve::downward(eve::sinh_1)(eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> sinh_1(as<wide_dt>())           = " << eve::sinh_1(eve::as<wide_dt>())                << std::endl
            << "-> sinh_1(as(wxd))                 = " << eve::sinh_1(eve::as(wxd))                      << std::endl
            << "-> upward(sinh_1)(as<wide_dt>())   = " << eve::upward(eve::sinh_1)(eve::as<wide_dt>())   << std::endl
            << "-> upward(sinh_1)(as(wxd))         = " << eve::upward(eve::sinh_1)(eve::as(wxd))         << std::endl
            << "-> downward(sinh_1)(as<wide_dt>()) = " << eve::downward(eve::sinh_1)(eve::as<wide_dt>()) << std::endl
            << "-> downward(sinh_1)(as(wxd))       = " << eve::downward(eve::sinh_1)(eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> sinh_1(as<float>())             = " << eve::sinh_1(eve::as(float())) << std::endl
            << "-> sinh_1(as<xf))                  = " << eve::sinh_1(eve::as(xf))      << std::endl
            << "-> sinh_1(as<double>())            = " << eve::sinh_1(eve::as(double()))<< std::endl
            << "-> sinh_1(as<xd))                  = " << eve::sinh_1(eve::as(xd))      << std::endl;

  return 0;
}
