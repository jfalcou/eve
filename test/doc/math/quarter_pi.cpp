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
            << "-> quarter_pi(as<wide_ft>())                 = " << eve::quarter_pi(eve::as<wide_ft>())                << std::endl
            << "-> quarter_pi(as(wxf))                       = " << eve::quarter_pi(eve::as(wxf))                      << std::endl
            << "-> upward(quarter_pi)(as<wide_ft>())         = " << eve::upward(eve::quarter_pi)(eve::as<wide_ft>())   << std::endl
            << "-> upward(quarter_pi)(as(wxf))               = " << eve::upward(eve::quarter_pi)(eve::as(wxf))         << std::endl
            << "-> downward(quarter_pi)(as<wide_ft>())       = " << eve::downward(eve::quarter_pi)(eve::as<wide_ft>()) << std::endl
            << "-> downward(quarter_pi)(as(wxf))             = " << eve::downward(eve::quarter_pi)(eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> quarter_pi(as<wide_dt>())           = " << eve::quarter_pi(eve::as<wide_dt>())                << std::endl
            << "-> quarter_pi(as(wxd))                 = " << eve::quarter_pi(eve::as(wxd))                      << std::endl
            << "-> upward(quarter_pi)(as<wide_dt>())   = " << eve::upward(eve::quarter_pi)(eve::as<wide_dt>())   << std::endl
            << "-> upward(quarter_pi)(as(wxd))         = " << eve::upward(eve::quarter_pi)(eve::as(wxd))         << std::endl
            << "-> downward(quarter_pi)(as<wide_dt>()) = " << eve::downward(eve::quarter_pi)(eve::as<wide_dt>()) << std::endl
            << "-> downward(quarter_pi)(as(wxd))       = " << eve::downward(eve::quarter_pi)(eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> quarter_pi(as<float>())             = " << eve::quarter_pi(eve::as(float())) << std::endl
            << "-> quarter_pi(as<xf))                  = " << eve::quarter_pi(eve::as(xf))      << std::endl
            << "-> quarter_pi(as<double>())            = " << eve::quarter_pi(eve::as(double()))<< std::endl
            << "-> quarter_pi(as<xd))                  = " << eve::quarter_pi(eve::as(xd))      << std::endl;

  return 0;
}
