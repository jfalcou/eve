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
            << "-> euler_pow_pi(as<wide_ft>())                 = " << eve::euler_pow_pi(eve::as<wide_ft>())                << std::endl
            << "-> euler_pow_pi(as(wxf))                       = " << eve::euler_pow_pi(eve::as(wxf))                      << std::endl
            << "-> upward(euler_pow_pi)(as<wide_ft>())         = " << eve::upward(eve::euler_pow_pi)(eve::as<wide_ft>())   << std::endl
            << "-> upward(euler_pow_pi)(as(wxf))               = " << eve::upward(eve::euler_pow_pi)(eve::as(wxf))         << std::endl
            << "-> downward(euler_pow_pi)(as<wide_ft>())       = " << eve::downward(eve::euler_pow_pi)(eve::as<wide_ft>()) << std::endl
            << "-> downward(euler_pow_pi)(as(wxf))             = " << eve::downward(eve::euler_pow_pi)(eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> euler_pow_pi(as<wide_dt>())           = " << eve::euler_pow_pi(eve::as<wide_dt>())                << std::endl
            << "-> euler_pow_pi(as(wxd))                 = " << eve::euler_pow_pi(eve::as(wxd))                      << std::endl
            << "-> upward(euler_pow_pi)(as<wide_dt>())   = " << eve::upward(eve::euler_pow_pi)(eve::as<wide_dt>())   << std::endl
            << "-> upward(euler_pow_pi)(as(wxd))         = " << eve::upward(eve::euler_pow_pi)(eve::as(wxd))         << std::endl
            << "-> downward(euler_pow_pi)(as<wide_dt>()) = " << eve::downward(eve::euler_pow_pi)(eve::as<wide_dt>()) << std::endl
            << "-> downward(euler_pow_pi)(as(wxd))       = " << eve::downward(eve::euler_pow_pi)(eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> euler_pow_pi(as<float>())             = " << eve::euler_pow_pi(eve::as(float())) << std::endl
            << "-> euler_pow_pi(as<xf))                  = " << eve::euler_pow_pi(eve::as(xf))      << std::endl
            << "-> euler_pow_pi(as<double>())            = " << eve::euler_pow_pi(eve::as(double()))<< std::endl
            << "-> euler_pow_pi(as<xd))                  = " << eve::euler_pow_pi(eve::as(xd))      << std::endl;

  return 0;
}
