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
            << "-> invlog10_e(as<wide_ft>())                 = " << eve::invlog10_e(eve::as<wide_ft>())                << std::endl
            << "-> invlog10_e(as(wxf))                       = " << eve::invlog10_e(eve::as(wxf))                      << std::endl
            << "-> upward(invlog10_e)(as<wide_ft>())         = " << eve::upward(eve::invlog10_e)(eve::as<wide_ft>())   << std::endl
            << "-> upward(invlog10_e)(as(wxf))               = " << eve::upward(eve::invlog10_e)(eve::as(wxf))         << std::endl
            << "-> downward(invlog10_e)(as<wide_ft>())       = " << eve::downward(eve::invlog10_e)(eve::as<wide_ft>()) << std::endl
            << "-> downward(invlog10_e)(as(wxf))             = " << eve::downward(eve::invlog10_e)(eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> invlog10_e(as<wide_dt>())           = " << eve::invlog10_e(eve::as<wide_dt>())                << std::endl
            << "-> invlog10_e(as(wxd))                 = " << eve::invlog10_e(eve::as(wxd))                      << std::endl
            << "-> upward(invlog10_e)(as<wide_dt>())   = " << eve::upward(eve::invlog10_e)(eve::as<wide_dt>())   << std::endl
            << "-> upward(invlog10_e)(as(wxd))         = " << eve::upward(eve::invlog10_e)(eve::as(wxd))         << std::endl
            << "-> downward(invlog10_e)(as<wide_dt>()) = " << eve::downward(eve::invlog10_e)(eve::as<wide_dt>()) << std::endl
            << "-> downward(invlog10_e)(as(wxd))       = " << eve::downward(eve::invlog10_e)(eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> invlog10_e(as<float>())             = " << eve::invlog10_e(eve::as(float())) << std::endl
            << "-> invlog10_e(as<xf))                  = " << eve::invlog10_e(eve::as(xf))      << std::endl
            << "-> invlog10_e(as<double>())            = " << eve::invlog10_e(eve::as(double()))<< std::endl
            << "-> invlog10_e(as<xd))                  = " << eve::invlog10_e(eve::as(xd))      << std::endl;

  return 0;
}
