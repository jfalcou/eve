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
            << "-> pi_pow_euler(as<wide_ft>())                 = " << eve::pi_pow_euler(eve::as<wide_ft>())                << std::endl
            << "-> pi_pow_euler(as(wxf))                       = " << eve::pi_pow_euler(eve::as(wxf))                      << std::endl
            << "-> upward(pi_pow_euler)(as<wide_ft>())         = " << eve::upward(eve::pi_pow_euler)(eve::as<wide_ft>())   << std::endl
            << "-> upward(pi_pow_euler)(as(wxf))               = " << eve::upward(eve::pi_pow_euler)(eve::as(wxf))         << std::endl
            << "-> downward(pi_pow_euler)(as<wide_ft>())       = " << eve::downward(eve::pi_pow_euler)(eve::as<wide_ft>()) << std::endl
            << "-> downward(pi_pow_euler)(as(wxf))             = " << eve::downward(eve::pi_pow_euler)(eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> pi_pow_euler(as<wide_dt>())           = " << eve::pi_pow_euler(eve::as<wide_dt>())                << std::endl
            << "-> pi_pow_euler(as(wxd))                 = " << eve::pi_pow_euler(eve::as(wxd))                      << std::endl
            << "-> upward(pi_pow_euler)(as<wide_dt>())   = " << eve::upward(eve::pi_pow_euler)(eve::as<wide_dt>())   << std::endl
            << "-> upward(pi_pow_euler)(as(wxd))         = " << eve::upward(eve::pi_pow_euler)(eve::as(wxd))         << std::endl
            << "-> downward(pi_pow_euler)(as<wide_dt>()) = " << eve::downward(eve::pi_pow_euler)(eve::as<wide_dt>()) << std::endl
            << "-> downward(pi_pow_euler)(as(wxd))       = " << eve::downward(eve::pi_pow_euler)(eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> pi_pow_euler(as<float>())             = " << eve::pi_pow_euler(eve::as(float())) << std::endl
            << "-> pi_pow_euler(as<xf))                  = " << eve::pi_pow_euler(eve::as(xf))      << std::endl
            << "-> pi_pow_euler(as<double>())            = " << eve::pi_pow_euler(eve::as(double()))<< std::endl
            << "-> pi_pow_euler(as<xd))                  = " << eve::pi_pow_euler(eve::as(xd))      << std::endl;

  return 0;
}
