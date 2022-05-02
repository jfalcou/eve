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
            << "-> cos_1(as<wide_ft>())                 = " << eve::cos_1(eve::as<wide_ft>())                << std::endl
            << "-> cos_1(as(wxf))                       = " << eve::cos_1(eve::as(wxf))                      << std::endl
            << "-> upward(cos_1)(as<wide_ft>())         = " << eve::upward(eve::cos_1)(eve::as<wide_ft>())   << std::endl
            << "-> upward(cos_1)(as(wxf))               = " << eve::upward(eve::cos_1)(eve::as(wxf))         << std::endl
            << "-> downward(cos_1)(as<wide_ft>())       = " << eve::downward(eve::cos_1)(eve::as<wide_ft>()) << std::endl
            << "-> downward(cos_1)(as(wxf))             = " << eve::downward(eve::cos_1)(eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> cos_1(as<wide_dt>())           = " << eve::cos_1(eve::as<wide_dt>())                << std::endl
            << "-> cos_1(as(wxd))                 = " << eve::cos_1(eve::as(wxd))                      << std::endl
            << "-> upward(cos_1)(as<wide_dt>())   = " << eve::upward(eve::cos_1)(eve::as<wide_dt>())   << std::endl
            << "-> upward(cos_1)(as(wxd))         = " << eve::upward(eve::cos_1)(eve::as(wxd))         << std::endl
            << "-> downward(cos_1)(as<wide_dt>()) = " << eve::downward(eve::cos_1)(eve::as<wide_dt>()) << std::endl
            << "-> downward(cos_1)(as(wxd))       = " << eve::downward(eve::cos_1)(eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> cos_1(as<float>())             = " << eve::cos_1(eve::as(float())) << std::endl
            << "-> cos_1(as<xf))                  = " << eve::cos_1(eve::as(xf))      << std::endl
            << "-> cos_1(as<double>())            = " << eve::cos_1(eve::as(double()))<< std::endl
            << "-> cos_1(as<xd))                  = " << eve::cos_1(eve::as(xd))      << std::endl;

  return 0;
}
