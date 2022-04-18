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
            << "-> sixth(as<wide_ft>())                 = " << eve::sixth(eve::as<wide_ft>())                << std::endl
            << "-> sixth(as(wxf))                       = " << eve::sixth(eve::as(wxf))                      << std::endl
            << "-> upward(sixth)(as<wide_ft>())         = " << eve::upward(eve::sixth)(eve::as<wide_ft>())   << std::endl
            << "-> upward(sixth)(as(wxf))               = " << eve::upward(eve::sixth)(eve::as(wxf))         << std::endl
            << "-> downward(sixth)(as<wide_ft>())       = " << eve::downward(eve::sixth)(eve::as<wide_ft>()) << std::endl
            << "-> downward(sixth)(as(wxf))             = " << eve::downward(eve::sixth)(eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> sixth(as<wide_dt>())           = " << eve::sixth(eve::as<wide_dt>())                << std::endl
            << "-> sixth(as(wxd))                 = " << eve::sixth(eve::as(wxd))                      << std::endl
            << "-> upward(sixth)(as<wide_dt>())   = " << eve::upward(eve::sixth)(eve::as<wide_dt>())   << std::endl
            << "-> upward(sixth)(as(wxd))         = " << eve::upward(eve::sixth)(eve::as(wxd))         << std::endl
            << "-> downward(sixth)(as<wide_dt>()) = " << eve::downward(eve::sixth)(eve::as<wide_dt>()) << std::endl
            << "-> downward(sixth)(as(wxd))       = " << eve::downward(eve::sixth)(eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> sixth(as<float>())             = " << eve::sixth(eve::as(float())) << std::endl
            << "-> sixth(as<xf))                  = " << eve::sixth(eve::as(xf))      << std::endl
            << "-> sixth(as<double>())            = " << eve::sixth(eve::as(double()))<< std::endl
            << "-> sixth(as<xd))                  = " << eve::sixth(eve::as(xd))      << std::endl;

  return 0;
}
