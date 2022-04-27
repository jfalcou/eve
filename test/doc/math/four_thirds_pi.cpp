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
            << "-> four_thirds_pi(as<wide_ft>())                 = " << eve::four_thirds_pi(eve::as<wide_ft>())                << std::endl
            << "-> four_thirds_pi(as(wxf))                       = " << eve::four_thirds_pi(eve::as(wxf))                      << std::endl
            << "-> upward(four_thirds_pi)(as<wide_ft>())         = " << eve::upward(eve::four_thirds_pi)(eve::as<wide_ft>())   << std::endl
            << "-> upward(four_thirds_pi)(as(wxf))               = " << eve::upward(eve::four_thirds_pi)(eve::as(wxf))         << std::endl
            << "-> downward(four_thirds_pi)(as<wide_ft>())       = " << eve::downward(eve::four_thirds_pi)(eve::as<wide_ft>()) << std::endl
            << "-> downward(four_thirds_pi)(as(wxf))             = " << eve::downward(eve::four_thirds_pi)(eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> four_thirds_pi(as<wide_dt>())           = " << eve::four_thirds_pi(eve::as<wide_dt>())                << std::endl
            << "-> four_thirds_pi(as(wxd))                 = " << eve::four_thirds_pi(eve::as(wxd))                      << std::endl
            << "-> upward(four_thirds_pi)(as<wide_dt>())   = " << eve::upward(eve::four_thirds_pi)(eve::as<wide_dt>())   << std::endl
            << "-> upward(four_thirds_pi)(as(wxd))         = " << eve::upward(eve::four_thirds_pi)(eve::as(wxd))         << std::endl
            << "-> downward(four_thirds_pi)(as<wide_dt>()) = " << eve::downward(eve::four_thirds_pi)(eve::as<wide_dt>()) << std::endl
            << "-> downward(four_thirds_pi)(as(wxd))       = " << eve::downward(eve::four_thirds_pi)(eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> four_thirds_pi(as<float>())             = " << eve::four_thirds_pi(eve::as(float())) << std::endl
            << "-> four_thirds_pi(as<xf))                  = " << eve::four_thirds_pi(eve::as(xf))      << std::endl
            << "-> four_thirds_pi(as<double>())            = " << eve::four_thirds_pi(eve::as(double()))<< std::endl
            << "-> four_thirds_pi(as<xd))                  = " << eve::four_thirds_pi(eve::as(xd))      << std::endl;

  return 0;
}
