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
            << "-> zeta_two(as<wide_ft>())                 = " << eve::zeta_two(eve::as<wide_ft>())                << std::endl
            << "-> zeta_two(as(wxf))                       = " << eve::zeta_two(eve::as(wxf))                      << std::endl
            << "-> upward(zeta_two)(as<wide_ft>())         = " << eve::upward(eve::zeta_two)(eve::as<wide_ft>())   << std::endl
            << "-> upward(zeta_two)(as(wxf))               = " << eve::upward(eve::zeta_two)(eve::as(wxf))         << std::endl
            << "-> downward(zeta_two)(as<wide_ft>())       = " << eve::downward(eve::zeta_two)(eve::as<wide_ft>()) << std::endl
            << "-> downward(zeta_two)(as(wxf))             = " << eve::downward(eve::zeta_two)(eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> zeta_two(as<wide_dt>())           = " << eve::zeta_two(eve::as<wide_dt>())                << std::endl
            << "-> zeta_two(as(wxd))                 = " << eve::zeta_two(eve::as(wxd))                      << std::endl
            << "-> upward(zeta_two)(as<wide_dt>())   = " << eve::upward(eve::zeta_two)(eve::as<wide_dt>())   << std::endl
            << "-> upward(zeta_two)(as(wxd))         = " << eve::upward(eve::zeta_two)(eve::as(wxd))         << std::endl
            << "-> downward(zeta_two)(as<wide_dt>()) = " << eve::downward(eve::zeta_two)(eve::as<wide_dt>()) << std::endl
            << "-> downward(zeta_two)(as(wxd))       = " << eve::downward(eve::zeta_two)(eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> zeta_two(as<float>())             = " << eve::zeta_two(eve::as(float())) << std::endl
            << "-> zeta_two(as<xf))                  = " << eve::zeta_two(eve::as(xf))      << std::endl
            << "-> zeta_two(as<double>())            = " << eve::zeta_two(eve::as(double()))<< std::endl
            << "-> zeta_two(as<xd))                  = " << eve::zeta_two(eve::as(xd))      << std::endl;

  return 0;
}
