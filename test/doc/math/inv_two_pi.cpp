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
            << "-> inv_two_pi(as<wide_ft>())                 = " << eve::inv_two_pi(eve::as<wide_ft>())                << std::endl
            << "-> inv_two_pi(as(wxf))                       = " << eve::inv_two_pi(eve::as(wxf))                      << std::endl
            << "-> upward(inv_two_pi)(as<wide_ft>())         = " << eve::upward(eve::inv_two_pi)(eve::as<wide_ft>())   << std::endl
            << "-> upward(inv_two_pi)(as(wxf))               = " << eve::upward(eve::inv_two_pi)(eve::as(wxf))         << std::endl
            << "-> downward(inv_two_pi)(as<wide_ft>())       = " << eve::downward(eve::inv_two_pi)(eve::as<wide_ft>()) << std::endl
            << "-> downward(inv_two_pi)(as(wxf))             = " << eve::downward(eve::inv_two_pi)(eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> inv_two_pi(as<wide_dt>())           = " << eve::inv_two_pi(eve::as<wide_dt>())                << std::endl
            << "-> inv_two_pi(as(wxd))                 = " << eve::inv_two_pi(eve::as(wxd))                      << std::endl
            << "-> upward(inv_two_pi)(as<wide_dt>())   = " << eve::upward(eve::inv_two_pi)(eve::as<wide_dt>())   << std::endl
            << "-> upward(inv_two_pi)(as(wxd))         = " << eve::upward(eve::inv_two_pi)(eve::as(wxd))         << std::endl
            << "-> downward(inv_two_pi)(as<wide_dt>()) = " << eve::downward(eve::inv_two_pi)(eve::as<wide_dt>()) << std::endl
            << "-> downward(inv_two_pi)(as(wxd))       = " << eve::downward(eve::inv_two_pi)(eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> inv_two_pi(as<float>())             = " << eve::inv_two_pi(eve::as(float())) << std::endl
            << "-> inv_two_pi(as<xf))                  = " << eve::inv_two_pi(eve::as(xf))      << std::endl
            << "-> inv_two_pi(as<double>())            = " << eve::inv_two_pi(eve::as(double()))<< std::endl
            << "-> inv_two_pi(as<xd))                  = " << eve::inv_two_pi(eve::as(xd))      << std::endl;

  return 0;
}
