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
            << "-> zeta_2(as<wide_ft>())                 = " << eve::zeta_2(eve::as<wide_ft>())                << std::endl
            << "-> zeta_2(as(wxf))                       = " << eve::zeta_2(eve::as(wxf))                      << std::endl
            << "-> upward(zeta_2)(as<wide_ft>())         = " << eve::upward(eve::zeta_2)(eve::as<wide_ft>())   << std::endl
            << "-> upward(zeta_2)(as(wxf))               = " << eve::upward(eve::zeta_2)(eve::as(wxf))         << std::endl
            << "-> downward(zeta_2)(as<wide_ft>())       = " << eve::downward(eve::zeta_2)(eve::as<wide_ft>()) << std::endl
            << "-> downward(zeta_2)(as(wxf))             = " << eve::downward(eve::zeta_2)(eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> zeta_2(as<wide_dt>())           = " << eve::zeta_2(eve::as<wide_dt>())                << std::endl
            << "-> zeta_2(as(wxd))                 = " << eve::zeta_2(eve::as(wxd))                      << std::endl
            << "-> upward(zeta_2)(as<wide_dt>())   = " << eve::upward(eve::zeta_2)(eve::as<wide_dt>())   << std::endl
            << "-> upward(zeta_2)(as(wxd))         = " << eve::upward(eve::zeta_2)(eve::as(wxd))         << std::endl
            << "-> downward(zeta_2)(as<wide_dt>()) = " << eve::downward(eve::zeta_2)(eve::as<wide_dt>()) << std::endl
            << "-> downward(zeta_2)(as(wxd))       = " << eve::downward(eve::zeta_2)(eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> zeta_2(as<float>())             = " << eve::zeta_2(eve::as(float())) << std::endl
            << "-> zeta_2(as<xf))                  = " << eve::zeta_2(eve::as(xf))      << std::endl
            << "-> zeta_2(as<double>())            = " << eve::zeta_2(eve::as(double()))<< std::endl
            << "-> zeta_2(as<xd))                  = " << eve::zeta_2(eve::as(xd))      << std::endl;

  return 0;
}
