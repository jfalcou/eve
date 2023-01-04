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
            << "-> pi_pow_e(as<wide_ft>())                 = " << eve::pi_pow_e(eve::as<wide_ft>())                << std::endl
            << "-> pi_pow_e(as(wxf))                       = " << eve::pi_pow_e(eve::as(wxf))                      << std::endl
            << "-> upward(pi_pow_e)(as<wide_ft>())         = " << eve::upward(eve::pi_pow_e)(eve::as<wide_ft>())   << std::endl
            << "-> upward(pi_pow_e)(as(wxf))               = " << eve::upward(eve::pi_pow_e)(eve::as(wxf))         << std::endl
            << "-> downward(pi_pow_e)(as<wide_ft>())       = " << eve::downward(eve::pi_pow_e)(eve::as<wide_ft>()) << std::endl
            << "-> downward(pi_pow_e)(as(wxf))             = " << eve::downward(eve::pi_pow_e)(eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> pi_pow_e(as<wide_dt>())           = " << eve::pi_pow_e(eve::as<wide_dt>())                << std::endl
            << "-> pi_pow_e(as(wxd))                 = " << eve::pi_pow_e(eve::as(wxd))                      << std::endl
            << "-> upward(pi_pow_e)(as<wide_dt>())   = " << eve::upward(eve::pi_pow_e)(eve::as<wide_dt>())   << std::endl
            << "-> upward(pi_pow_e)(as(wxd))         = " << eve::upward(eve::pi_pow_e)(eve::as(wxd))         << std::endl
            << "-> downward(pi_pow_e)(as<wide_dt>()) = " << eve::downward(eve::pi_pow_e)(eve::as<wide_dt>()) << std::endl
            << "-> downward(pi_pow_e)(as(wxd))       = " << eve::downward(eve::pi_pow_e)(eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> pi_pow_e(as<float>())             = " << eve::pi_pow_e(eve::as(float())) << std::endl
            << "-> pi_pow_e(as<xf))                  = " << eve::pi_pow_e(eve::as(xf))      << std::endl
            << "-> pi_pow_e(as<double>())            = " << eve::pi_pow_e(eve::as(double()))<< std::endl
            << "-> pi_pow_e(as<xd))                  = " << eve::pi_pow_e(eve::as(xd))      << std::endl;

  return 0;
}
