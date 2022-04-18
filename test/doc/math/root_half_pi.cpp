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
            << "-> root_half_pi(as<wide_ft>())                 = " << eve::root_half_pi(eve::as<wide_ft>())                << std::endl
            << "-> root_half_pi(as(wxf))                       = " << eve::root_half_pi(eve::as(wxf))                      << std::endl
            << "-> upward(root_half_pi)(as<wide_ft>())         = " << eve::upward(eve::root_half_pi)(eve::as<wide_ft>())   << std::endl
            << "-> upward(root_half_pi)(as(wxf))               = " << eve::upward(eve::root_half_pi)(eve::as(wxf))         << std::endl
            << "-> downward(root_half_pi)(as<wide_ft>())       = " << eve::downward(eve::root_half_pi)(eve::as<wide_ft>()) << std::endl
            << "-> downward(root_half_pi)(as(wxf))             = " << eve::downward(eve::root_half_pi)(eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> root_half_pi(as<wide_dt>())           = " << eve::root_half_pi(eve::as<wide_dt>())                << std::endl
            << "-> root_half_pi(as(wxd))                 = " << eve::root_half_pi(eve::as(wxd))                      << std::endl
            << "-> upward(root_half_pi)(as<wide_dt>())   = " << eve::upward(eve::root_half_pi)(eve::as<wide_dt>())   << std::endl
            << "-> upward(root_half_pi)(as(wxd))         = " << eve::upward(eve::root_half_pi)(eve::as(wxd))         << std::endl
            << "-> downward(root_half_pi)(as<wide_dt>()) = " << eve::downward(eve::root_half_pi)(eve::as<wide_dt>()) << std::endl
            << "-> downward(root_half_pi)(as(wxd))       = " << eve::downward(eve::root_half_pi)(eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> root_half_pi(as<float>())             = " << eve::root_half_pi(eve::as(float())) << std::endl
            << "-> root_half_pi(as<xf))                  = " << eve::root_half_pi(eve::as(xf))      << std::endl
            << "-> root_half_pi(as<double>())            = " << eve::root_half_pi(eve::as(double()))<< std::endl
            << "-> root_half_pi(as<xd))                  = " << eve::root_half_pi(eve::as(xd))      << std::endl;

  return 0;
}
