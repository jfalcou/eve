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
            << "-> zeta_three(as<wide_ft>())                 = " << eve::zeta_three(eve::as<wide_ft>())                << std::endl
            << "-> zeta_three(as(wxf))                       = " << eve::zeta_three(eve::as(wxf))                      << std::endl
            << "-> upward(zeta_three)(as<wide_ft>())         = " << eve::upward(eve::zeta_three)(eve::as<wide_ft>())   << std::endl
            << "-> upward(zeta_three)(as(wxf))               = " << eve::upward(eve::zeta_three)(eve::as(wxf))         << std::endl
            << "-> downward(zeta_three)(as<wide_ft>())       = " << eve::downward(eve::zeta_three)(eve::as<wide_ft>()) << std::endl
            << "-> downward(zeta_three)(as(wxf))             = " << eve::downward(eve::zeta_three)(eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> zeta_three(as<wide_dt>())           = " << eve::zeta_three(eve::as<wide_dt>())                << std::endl
            << "-> zeta_three(as(wxd))                 = " << eve::zeta_three(eve::as(wxd))                      << std::endl
            << "-> upward(zeta_three)(as<wide_dt>())   = " << eve::upward(eve::zeta_three)(eve::as<wide_dt>())   << std::endl
            << "-> upward(zeta_three)(as(wxd))         = " << eve::upward(eve::zeta_three)(eve::as(wxd))         << std::endl
            << "-> downward(zeta_three)(as<wide_dt>()) = " << eve::downward(eve::zeta_three)(eve::as<wide_dt>()) << std::endl
            << "-> downward(zeta_three)(as(wxd))       = " << eve::downward(eve::zeta_three)(eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> zeta_three(as<float>())             = " << eve::zeta_three(eve::as(float())) << std::endl
            << "-> zeta_three(as<xf))                  = " << eve::zeta_three(eve::as(xf))      << std::endl
            << "-> zeta_three(as<double>())            = " << eve::zeta_three(eve::as(double()))<< std::endl
            << "-> zeta_three(as<xd))                  = " << eve::zeta_three(eve::as(xd))      << std::endl;

  return 0;
}
