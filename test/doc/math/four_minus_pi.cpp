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
            << "-> four_minus_pi(as<wide_ft>())                 = " << eve::four_minus_pi(eve::as<wide_ft>())                << std::endl
            << "-> four_minus_pi(as(wxf))                       = " << eve::four_minus_pi(eve::as(wxf))                      << std::endl
            << "-> upward(four_minus_pi)(as<wide_ft>())         = " << eve::upward(eve::four_minus_pi)(eve::as<wide_ft>())   << std::endl
            << "-> upward(four_minus_pi)(as(wxf))               = " << eve::upward(eve::four_minus_pi)(eve::as(wxf))         << std::endl
            << "-> downward(four_minus_pi)(as<wide_ft>())       = " << eve::downward(eve::four_minus_pi)(eve::as<wide_ft>()) << std::endl
            << "-> downward(four_minus_pi)(as(wxf))             = " << eve::downward(eve::four_minus_pi)(eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> four_minus_pi(as<wide_dt>())           = " << eve::four_minus_pi(eve::as<wide_dt>())                << std::endl
            << "-> four_minus_pi(as(wxd))                 = " << eve::four_minus_pi(eve::as(wxd))                      << std::endl
            << "-> upward(four_minus_pi)(as<wide_dt>())   = " << eve::upward(eve::four_minus_pi)(eve::as<wide_dt>())   << std::endl
            << "-> upward(four_minus_pi)(as(wxd))         = " << eve::upward(eve::four_minus_pi)(eve::as(wxd))         << std::endl
            << "-> downward(four_minus_pi)(as<wide_dt>()) = " << eve::downward(eve::four_minus_pi)(eve::as<wide_dt>()) << std::endl
            << "-> downward(four_minus_pi)(as(wxd))       = " << eve::downward(eve::four_minus_pi)(eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> four_minus_pi(as<float>())             = " << eve::four_minus_pi(eve::as(float())) << std::endl
            << "-> four_minus_pi(as<xf))                  = " << eve::four_minus_pi(eve::as(xf))      << std::endl
            << "-> four_minus_pi(as<double>())            = " << eve::four_minus_pi(eve::as(double()))<< std::endl
            << "-> four_minus_pi(as<xd))                  = " << eve::four_minus_pi(eve::as(xd))      << std::endl;

  return 0;
}
