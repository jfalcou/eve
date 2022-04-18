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
            << "-> two_thirds(as<wide_ft>())                 = " << eve::two_thirds(eve::as<wide_ft>())                << std::endl
            << "-> two_thirds(as(wxf))                       = " << eve::two_thirds(eve::as(wxf))                      << std::endl
            << "-> upward(two_thirds)(as<wide_ft>())         = " << eve::upward(eve::two_thirds)(eve::as<wide_ft>())   << std::endl
            << "-> upward(two_thirds)(as(wxf))               = " << eve::upward(eve::two_thirds)(eve::as(wxf))         << std::endl
            << "-> downward(two_thirds)(as<wide_ft>())       = " << eve::downward(eve::two_thirds)(eve::as<wide_ft>()) << std::endl
            << "-> downward(two_thirds)(as(wxf))             = " << eve::downward(eve::two_thirds)(eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> two_thirds(as<wide_dt>())           = " << eve::two_thirds(eve::as<wide_dt>())                << std::endl
            << "-> two_thirds(as(wxd))                 = " << eve::two_thirds(eve::as(wxd))                      << std::endl
            << "-> upward(two_thirds)(as<wide_dt>())   = " << eve::upward(eve::two_thirds)(eve::as<wide_dt>())   << std::endl
            << "-> upward(two_thirds)(as(wxd))         = " << eve::upward(eve::two_thirds)(eve::as(wxd))         << std::endl
            << "-> downward(two_thirds)(as<wide_dt>()) = " << eve::downward(eve::two_thirds)(eve::as<wide_dt>()) << std::endl
            << "-> downward(two_thirds)(as(wxd))       = " << eve::downward(eve::two_thirds)(eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> two_thirds(as<float>())             = " << eve::two_thirds(eve::as(float())) << std::endl
            << "-> two_thirds(as<xf))                  = " << eve::two_thirds(eve::as(xf))      << std::endl
            << "-> two_thirds(as<double>())            = " << eve::two_thirds(eve::as(double()))<< std::endl
            << "-> two_thirds(as<xd))                  = " << eve::two_thirds(eve::as(xd))      << std::endl;

  return 0;
}
