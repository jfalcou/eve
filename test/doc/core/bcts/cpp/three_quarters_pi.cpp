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
            << "-> three_quarters_pi(as<wide_ft>())                 = " << eve::three_quarters_pi(eve::as<wide_ft>())                << std::endl
            << "-> three_quarters_pi(as(wxf))                       = " << eve::three_quarters_pi(eve::as(wxf))                      << std::endl
            << "-> upward(three_quarters_pi)(as<wide_ft>())         = " << eve::upward(eve::three_quarters_pi)(eve::as<wide_ft>())   << std::endl
            << "-> upward(three_quarters_pi)(as(wxf))               = " << eve::upward(eve::three_quarters_pi)(eve::as(wxf))         << std::endl
            << "-> downward(three_quarters_pi)(as<wide_ft>())       = " << eve::downward(eve::three_quarters_pi)(eve::as<wide_ft>()) << std::endl
            << "-> downward(three_quarters_pi)(as(wxf))             = " << eve::downward(eve::three_quarters_pi)(eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> three_quarters_pi(as<wide_dt>())           = " << eve::three_quarters_pi(eve::as<wide_dt>())                << std::endl
            << "-> three_quarters_pi(as(wxd))                 = " << eve::three_quarters_pi(eve::as(wxd))                      << std::endl
            << "-> upward(three_quarters_pi)(as<wide_dt>())   = " << eve::upward(eve::three_quarters_pi)(eve::as<wide_dt>())   << std::endl
            << "-> upward(three_quarters_pi)(as(wxd))         = " << eve::upward(eve::three_quarters_pi)(eve::as(wxd))         << std::endl
            << "-> downward(three_quarters_pi)(as<wide_dt>()) = " << eve::downward(eve::three_quarters_pi)(eve::as<wide_dt>()) << std::endl
            << "-> downward(three_quarters_pi)(as(wxd))       = " << eve::downward(eve::three_quarters_pi)(eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> three_quarters_pi(as<float>())             = " << eve::three_quarters_pi(eve::as(float())) << std::endl
            << "-> three_quarters_pi(as<xf))                  = " << eve::three_quarters_pi(eve::as(xf))      << std::endl
            << "-> three_quarters_pi(as<double>())            = " << eve::three_quarters_pi(eve::as(double()))<< std::endl
            << "-> three_quarters_pi(as<xd))                  = " << eve::three_quarters_pi(eve::as(xd))      << std::endl;

  return 0;
}
