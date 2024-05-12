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
            << "-> pi_minus_3(as<wide_ft>())                 = " << eve::pi_minus_3(eve::as<wide_ft>())                << std::endl
            << "-> pi_minus_3(as(wxf))                       = " << eve::pi_minus_3(eve::as(wxf))                      << std::endl
            << "-> upward(pi_minus_3)(as<wide_ft>())         = " << eve::upward(eve::pi_minus_3)(eve::as<wide_ft>())   << std::endl
            << "-> upward(pi_minus_3)(as(wxf))               = " << eve::upward(eve::pi_minus_3)(eve::as(wxf))         << std::endl
            << "-> downward(pi_minus_3)(as<wide_ft>())       = " << eve::downward(eve::pi_minus_3)(eve::as<wide_ft>()) << std::endl
            << "-> downward(pi_minus_3)(as(wxf))             = " << eve::downward(eve::pi_minus_3)(eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> pi_minus_3(as<wide_dt>())           = " << eve::pi_minus_3(eve::as<wide_dt>())                << std::endl
            << "-> pi_minus_3(as(wxd))                 = " << eve::pi_minus_3(eve::as(wxd))                      << std::endl
            << "-> upward(pi_minus_3)(as<wide_dt>())   = " << eve::upward(eve::pi_minus_3)(eve::as<wide_dt>())   << std::endl
            << "-> upward(pi_minus_3)(as(wxd))         = " << eve::upward(eve::pi_minus_3)(eve::as(wxd))         << std::endl
            << "-> downward(pi_minus_3)(as<wide_dt>()) = " << eve::downward(eve::pi_minus_3)(eve::as<wide_dt>()) << std::endl
            << "-> downward(pi_minus_3)(as(wxd))       = " << eve::downward(eve::pi_minus_3)(eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> pi_minus_3(as<float>())             = " << eve::pi_minus_3(eve::as(float())) << std::endl
            << "-> pi_minus_3(as<xf))                  = " << eve::pi_minus_3(eve::as(xf))      << std::endl
            << "-> pi_minus_3(as<double>())            = " << eve::pi_minus_3(eve::as(double()))<< std::endl
            << "-> pi_minus_3(as<xd))                  = " << eve::pi_minus_3(eve::as(xd))      << std::endl;

  return 0;
}
