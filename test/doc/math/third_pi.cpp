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
            << "-> third_pi(as<wide_ft>())                 = " << eve::third_pi(eve::as<wide_ft>())                << std::endl
            << "-> third_pi(as(wxf))                       = " << eve::third_pi(eve::as(wxf))                      << std::endl
            << "-> upward(third_pi)(as<wide_ft>())         = " << eve::upward(eve::third_pi)(eve::as<wide_ft>())   << std::endl
            << "-> upward(third_pi)(as(wxf))               = " << eve::upward(eve::third_pi)(eve::as(wxf))         << std::endl
            << "-> downward(third_pi)(as<wide_ft>())       = " << eve::downward(eve::third_pi)(eve::as<wide_ft>()) << std::endl
            << "-> downward(third_pi)(as(wxf))             = " << eve::downward(eve::third_pi)(eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> third_pi(as<wide_dt>())           = " << eve::third_pi(eve::as<wide_dt>())                << std::endl
            << "-> third_pi(as(wxd))                 = " << eve::third_pi(eve::as(wxd))                      << std::endl
            << "-> upward(third_pi)(as<wide_dt>())   = " << eve::upward(eve::third_pi)(eve::as<wide_dt>())   << std::endl
            << "-> upward(third_pi)(as(wxd))         = " << eve::upward(eve::third_pi)(eve::as(wxd))         << std::endl
            << "-> downward(third_pi)(as<wide_dt>()) = " << eve::downward(eve::third_pi)(eve::as<wide_dt>()) << std::endl
            << "-> downward(third_pi)(as(wxd))       = " << eve::downward(eve::third_pi)(eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> third_pi(as<float>())             = " << eve::third_pi(eve::as(float())) << std::endl
            << "-> third_pi(as<xf))                  = " << eve::third_pi(eve::as(xf))      << std::endl
            << "-> third_pi(as<double>())            = " << eve::third_pi(eve::as(double()))<< std::endl
            << "-> third_pi(as<xd))                  = " << eve::third_pi(eve::as(xd))      << std::endl;

  return 0;
}
