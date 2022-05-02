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
            << "-> pi2(as<wide_ft>())                 = " << eve::pi2(eve::as<wide_ft>())                << std::endl
            << "-> pi2(as(wxf))                       = " << eve::pi2(eve::as(wxf))                      << std::endl
            << "-> upward(pi2)(as<wide_ft>())         = " << eve::upward(eve::pi2)(eve::as<wide_ft>())   << std::endl
            << "-> upward(pi2)(as(wxf))               = " << eve::upward(eve::pi2)(eve::as(wxf))         << std::endl
            << "-> downward(pi2)(as<wide_ft>())       = " << eve::downward(eve::pi2)(eve::as<wide_ft>()) << std::endl
            << "-> downward(pi2)(as(wxf))             = " << eve::downward(eve::pi2)(eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> pi2(as<wide_dt>())           = " << eve::pi2(eve::as<wide_dt>())                << std::endl
            << "-> pi2(as(wxd))                 = " << eve::pi2(eve::as(wxd))                      << std::endl
            << "-> upward(pi2)(as<wide_dt>())   = " << eve::upward(eve::pi2)(eve::as<wide_dt>())   << std::endl
            << "-> upward(pi2)(as(wxd))         = " << eve::upward(eve::pi2)(eve::as(wxd))         << std::endl
            << "-> downward(pi2)(as<wide_dt>()) = " << eve::downward(eve::pi2)(eve::as<wide_dt>()) << std::endl
            << "-> downward(pi2)(as(wxd))       = " << eve::downward(eve::pi2)(eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> pi2(as<float>())             = " << eve::pi2(eve::as(float())) << std::endl
            << "-> pi2(as<xf))                  = " << eve::pi2(eve::as(xf))      << std::endl
            << "-> pi2(as<double>())            = " << eve::pi2(eve::as(double()))<< std::endl
            << "-> pi2(as<xd))                  = " << eve::pi2(eve::as(xd))      << std::endl;

  return 0;
}
