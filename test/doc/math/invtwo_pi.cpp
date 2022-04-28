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
            << "-> invtwo_pi(as<wide_ft>())                 = " << eve::invtwo_pi(eve::as<wide_ft>())                << std::endl
            << "-> invtwo_pi(as(wxf))                       = " << eve::invtwo_pi(eve::as(wxf))                      << std::endl
            << "-> upward(invtwo_pi)(as<wide_ft>())         = " << eve::upward(eve::invtwo_pi)(eve::as<wide_ft>())   << std::endl
            << "-> upward(invtwo_pi)(as(wxf))               = " << eve::upward(eve::invtwo_pi)(eve::as(wxf))         << std::endl
            << "-> downward(invtwo_pi)(as<wide_ft>())       = " << eve::downward(eve::invtwo_pi)(eve::as<wide_ft>()) << std::endl
            << "-> downward(invtwo_pi)(as(wxf))             = " << eve::downward(eve::invtwo_pi)(eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> invtwo_pi(as<wide_dt>())           = " << eve::invtwo_pi(eve::as<wide_dt>())                << std::endl
            << "-> invtwo_pi(as(wxd))                 = " << eve::invtwo_pi(eve::as(wxd))                      << std::endl
            << "-> upward(invtwo_pi)(as<wide_dt>())   = " << eve::upward(eve::invtwo_pi)(eve::as<wide_dt>())   << std::endl
            << "-> upward(invtwo_pi)(as(wxd))         = " << eve::upward(eve::invtwo_pi)(eve::as(wxd))         << std::endl
            << "-> downward(invtwo_pi)(as<wide_dt>()) = " << eve::downward(eve::invtwo_pi)(eve::as<wide_dt>()) << std::endl
            << "-> downward(invtwo_pi)(as(wxd))       = " << eve::downward(eve::invtwo_pi)(eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> invtwo_pi(as<float>())             = " << eve::invtwo_pi(eve::as(float())) << std::endl
            << "-> invtwo_pi(as<xf))                  = " << eve::invtwo_pi(eve::as(xf))      << std::endl
            << "-> invtwo_pi(as<double>())            = " << eve::invtwo_pi(eve::as(double()))<< std::endl
            << "-> invtwo_pi(as<xd))                  = " << eve::invtwo_pi(eve::as(xd))      << std::endl;

  return 0;
}
