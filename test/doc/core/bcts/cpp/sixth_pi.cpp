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
            << "-> sixth_pi(as<wide_ft>())                 = " << eve::sixth_pi(eve::as<wide_ft>())                << std::endl
            << "-> sixth_pi(as(wxf))                       = " << eve::sixth_pi(eve::as(wxf))                      << std::endl
            << "-> upward(sixth_pi)(as<wide_ft>())         = " << eve::upward(eve::sixth_pi)(eve::as<wide_ft>())   << std::endl
            << "-> upward(sixth_pi)(as(wxf))               = " << eve::upward(eve::sixth_pi)(eve::as(wxf))         << std::endl
            << "-> downward(sixth_pi)(as<wide_ft>())       = " << eve::downward(eve::sixth_pi)(eve::as<wide_ft>()) << std::endl
            << "-> downward(sixth_pi)(as(wxf))             = " << eve::downward(eve::sixth_pi)(eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> sixth_pi(as<wide_dt>())           = " << eve::sixth_pi(eve::as<wide_dt>())                << std::endl
            << "-> sixth_pi(as(wxd))                 = " << eve::sixth_pi(eve::as(wxd))                      << std::endl
            << "-> upward(sixth_pi)(as<wide_dt>())   = " << eve::upward(eve::sixth_pi)(eve::as<wide_dt>())   << std::endl
            << "-> upward(sixth_pi)(as(wxd))         = " << eve::upward(eve::sixth_pi)(eve::as(wxd))         << std::endl
            << "-> downward(sixth_pi)(as<wide_dt>()) = " << eve::downward(eve::sixth_pi)(eve::as<wide_dt>()) << std::endl
            << "-> downward(sixth_pi)(as(wxd))       = " << eve::downward(eve::sixth_pi)(eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> sixth_pi(as<float>())             = " << eve::sixth_pi(eve::as(float())) << std::endl
            << "-> sixth_pi(as<xf))                  = " << eve::sixth_pi(eve::as(xf))      << std::endl
            << "-> sixth_pi(as<double>())            = " << eve::sixth_pi(eve::as(double()))<< std::endl
            << "-> sixth_pi(as<xd))                  = " << eve::sixth_pi(eve::as(xd))      << std::endl;

  return 0;
}
