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
            << "-> cbrt_pi(as<wide_ft>())                 = " << eve::cbrt_pi(eve::as<wide_ft>())                << std::endl
            << "-> cbrt_pi(as(wxf))                       = " << eve::cbrt_pi(eve::as(wxf))                      << std::endl
            << "-> upward(cbrt_pi)(as<wide_ft>())         = " << eve::upward(eve::cbrt_pi)(eve::as<wide_ft>())   << std::endl
            << "-> upward(cbrt_pi)(as(wxf))               = " << eve::upward(eve::cbrt_pi)(eve::as(wxf))         << std::endl
            << "-> downward(cbrt_pi)(as<wide_ft>())       = " << eve::downward(eve::cbrt_pi)(eve::as<wide_ft>()) << std::endl
            << "-> downward(cbrt_pi)(as(wxf))             = " << eve::downward(eve::cbrt_pi)(eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> cbrt_pi(as<wide_dt>())           = " << eve::cbrt_pi(eve::as<wide_dt>())                << std::endl
            << "-> cbrt_pi(as(wxd))                 = " << eve::cbrt_pi(eve::as(wxd))                      << std::endl
            << "-> upward(cbrt_pi)(as<wide_dt>())   = " << eve::upward(eve::cbrt_pi)(eve::as<wide_dt>())   << std::endl
            << "-> upward(cbrt_pi)(as(wxd))         = " << eve::upward(eve::cbrt_pi)(eve::as(wxd))         << std::endl
            << "-> downward(cbrt_pi)(as<wide_dt>()) = " << eve::downward(eve::cbrt_pi)(eve::as<wide_dt>()) << std::endl
            << "-> downward(cbrt_pi)(as(wxd))       = " << eve::downward(eve::cbrt_pi)(eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> cbrt_pi(as<float>())             = " << eve::cbrt_pi(eve::as(float())) << std::endl
            << "-> cbrt_pi(as<xf))                  = " << eve::cbrt_pi(eve::as(xf))      << std::endl
            << "-> cbrt_pi(as<double>())            = " << eve::cbrt_pi(eve::as(double()))<< std::endl
            << "-> cbrt_pi(as<xd))                  = " << eve::cbrt_pi(eve::as(xd))      << std::endl;

  return 0;
}
