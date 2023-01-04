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
            << "-> sqrt_pi(as<wide_ft>())                 = " << eve::sqrt_pi(eve::as<wide_ft>())                << std::endl
            << "-> sqrt_pi(as(wxf))                       = " << eve::sqrt_pi(eve::as(wxf))                      << std::endl
            << "-> upward(sqrt_pi)(as<wide_ft>())         = " << eve::upward(eve::sqrt_pi)(eve::as<wide_ft>())   << std::endl
            << "-> upward(sqrt_pi)(as(wxf))               = " << eve::upward(eve::sqrt_pi)(eve::as(wxf))         << std::endl
            << "-> downward(sqrt_pi)(as<wide_ft>())       = " << eve::downward(eve::sqrt_pi)(eve::as<wide_ft>()) << std::endl
            << "-> downward(sqrt_pi)(as(wxf))             = " << eve::downward(eve::sqrt_pi)(eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> sqrt_pi(as<wide_dt>())           = " << eve::sqrt_pi(eve::as<wide_dt>())                << std::endl
            << "-> sqrt_pi(as(wxd))                 = " << eve::sqrt_pi(eve::as(wxd))                      << std::endl
            << "-> upward(sqrt_pi)(as<wide_dt>())   = " << eve::upward(eve::sqrt_pi)(eve::as<wide_dt>())   << std::endl
            << "-> upward(sqrt_pi)(as(wxd))         = " << eve::upward(eve::sqrt_pi)(eve::as(wxd))         << std::endl
            << "-> downward(sqrt_pi)(as<wide_dt>()) = " << eve::downward(eve::sqrt_pi)(eve::as<wide_dt>()) << std::endl
            << "-> downward(sqrt_pi)(as(wxd))       = " << eve::downward(eve::sqrt_pi)(eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> sqrt_pi(as<float>())             = " << eve::sqrt_pi(eve::as(float())) << std::endl
            << "-> sqrt_pi(as<xf))                  = " << eve::sqrt_pi(eve::as(xf))      << std::endl
            << "-> sqrt_pi(as<double>())            = " << eve::sqrt_pi(eve::as(double()))<< std::endl
            << "-> sqrt_pi(as<xd))                  = " << eve::sqrt_pi(eve::as(xd))      << std::endl;

  return 0;
}
