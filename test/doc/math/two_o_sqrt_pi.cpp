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
            << "-> two_o_sqrt_pi(as<wide_ft>())                 = " << eve::two_o_sqrt_pi(eve::as<wide_ft>())                << std::endl
            << "-> two_o_sqrt_pi(as(wxf))                       = " << eve::two_o_sqrt_pi(eve::as(wxf))                      << std::endl
            << "-> upward(two_o_sqrt_pi)(as<wide_ft>())         = " << eve::upward(eve::two_o_sqrt_pi)(eve::as<wide_ft>())   << std::endl
            << "-> upward(two_o_sqrt_pi)(as(wxf))               = " << eve::upward(eve::two_o_sqrt_pi)(eve::as(wxf))         << std::endl
            << "-> downward(two_o_sqrt_pi)(as<wide_ft>())       = " << eve::downward(eve::two_o_sqrt_pi)(eve::as<wide_ft>()) << std::endl
            << "-> downward(two_o_sqrt_pi)(as(wxf))             = " << eve::downward(eve::two_o_sqrt_pi)(eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> two_o_sqrt_pi(as<wide_dt>())           = " << eve::two_o_sqrt_pi(eve::as<wide_dt>())                << std::endl
            << "-> two_o_sqrt_pi(as(wxd))                 = " << eve::two_o_sqrt_pi(eve::as(wxd))                      << std::endl
            << "-> upward(two_o_sqrt_pi)(as<wide_dt>())   = " << eve::upward(eve::two_o_sqrt_pi)(eve::as<wide_dt>())   << std::endl
            << "-> upward(two_o_sqrt_pi)(as(wxd))         = " << eve::upward(eve::two_o_sqrt_pi)(eve::as(wxd))         << std::endl
            << "-> downward(two_o_sqrt_pi)(as<wide_dt>()) = " << eve::downward(eve::two_o_sqrt_pi)(eve::as<wide_dt>()) << std::endl
            << "-> downward(two_o_sqrt_pi)(as(wxd))       = " << eve::downward(eve::two_o_sqrt_pi)(eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> two_o_sqrt_pi(as<float>())             = " << eve::two_o_sqrt_pi(eve::as(float())) << std::endl
            << "-> two_o_sqrt_pi(as<xf))                  = " << eve::two_o_sqrt_pi(eve::as(xf))      << std::endl
            << "-> two_o_sqrt_pi(as<double>())            = " << eve::two_o_sqrt_pi(eve::as(double()))<< std::endl
            << "-> two_o_sqrt_pi(as<xd))                  = " << eve::two_o_sqrt_pi(eve::as(xd))      << std::endl;

  return 0;
}
