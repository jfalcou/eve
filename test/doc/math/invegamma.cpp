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
            << "-> invegamma(as<wide_ft>())                 = " << eve::invegamma(eve::as<wide_ft>())                << std::endl
            << "-> invegamma(as(wxf))                       = " << eve::invegamma(eve::as(wxf))                      << std::endl
            << "-> upward(invegamma)(as<wide_ft>())         = " << eve::upward(eve::invegamma)(eve::as<wide_ft>())   << std::endl
            << "-> upward(invegamma)(as(wxf))               = " << eve::upward(eve::invegamma)(eve::as(wxf))         << std::endl
            << "-> downward(invegamma)(as<wide_ft>())       = " << eve::downward(eve::invegamma)(eve::as<wide_ft>()) << std::endl
            << "-> downward(invegamma)(as(wxf))             = " << eve::downward(eve::invegamma)(eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> invegamma(as<wide_dt>())           = " << eve::invegamma(eve::as<wide_dt>())                << std::endl
            << "-> invegamma(as(wxd))                 = " << eve::invegamma(eve::as(wxd))                      << std::endl
            << "-> upward(invegamma)(as<wide_dt>())   = " << eve::upward(eve::invegamma)(eve::as<wide_dt>())   << std::endl
            << "-> upward(invegamma)(as(wxd))         = " << eve::upward(eve::invegamma)(eve::as(wxd))         << std::endl
            << "-> downward(invegamma)(as<wide_dt>()) = " << eve::downward(eve::invegamma)(eve::as<wide_dt>()) << std::endl
            << "-> downward(invegamma)(as(wxd))       = " << eve::downward(eve::invegamma)(eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> invegamma(as<float>())             = " << eve::invegamma(eve::as(float())) << std::endl
            << "-> invegamma(as<xf))                  = " << eve::invegamma(eve::as(xf))      << std::endl
            << "-> invegamma(as<double>())            = " << eve::invegamma(eve::as(double()))<< std::endl
            << "-> invegamma(as<xd))                  = " << eve::invegamma(eve::as(xd))      << std::endl;

  return 0;
}
