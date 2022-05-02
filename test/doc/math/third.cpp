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
            << "-> third(as<wide_ft>())                 = " << eve::third(eve::as<wide_ft>())                << std::endl
            << "-> third(as(wxf))                       = " << eve::third(eve::as(wxf))                      << std::endl
            << "-> upward(third)(as<wide_ft>())         = " << eve::upward(eve::third)(eve::as<wide_ft>())   << std::endl
            << "-> upward(third)(as(wxf))               = " << eve::upward(eve::third)(eve::as(wxf))         << std::endl
            << "-> downward(third)(as<wide_ft>())       = " << eve::downward(eve::third)(eve::as<wide_ft>()) << std::endl
            << "-> downward(third)(as(wxf))             = " << eve::downward(eve::third)(eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> third(as<wide_dt>())           = " << eve::third(eve::as<wide_dt>())                << std::endl
            << "-> third(as(wxd))                 = " << eve::third(eve::as(wxd))                      << std::endl
            << "-> upward(third)(as<wide_dt>())   = " << eve::upward(eve::third)(eve::as<wide_dt>())   << std::endl
            << "-> upward(third)(as(wxd))         = " << eve::upward(eve::third)(eve::as(wxd))         << std::endl
            << "-> downward(third)(as<wide_dt>()) = " << eve::downward(eve::third)(eve::as<wide_dt>()) << std::endl
            << "-> downward(third)(as(wxd))       = " << eve::downward(eve::third)(eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> third(as<float>())             = " << eve::third(eve::as(float())) << std::endl
            << "-> third(as<xf))                  = " << eve::third(eve::as(xf))      << std::endl
            << "-> third(as<double>())            = " << eve::third(eve::as(double()))<< std::endl
            << "-> third(as<xd))                  = " << eve::third(eve::as(xd))      << std::endl;

  return 0;
}
