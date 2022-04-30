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
            << "-> sqrt_e(as<wide_ft>())                 = " << eve::sqrt_e(eve::as<wide_ft>())                << std::endl
            << "-> sqrt_e(as(wxf))                       = " << eve::sqrt_e(eve::as(wxf))                      << std::endl
            << "-> upward(sqrt_e)(as<wide_ft>())         = " << eve::upward(eve::sqrt_e)(eve::as<wide_ft>())   << std::endl
            << "-> upward(sqrt_e)(as(wxf))               = " << eve::upward(eve::sqrt_e)(eve::as(wxf))         << std::endl
            << "-> downward(sqrt_e)(as<wide_ft>())       = " << eve::downward(eve::sqrt_e)(eve::as<wide_ft>()) << std::endl
            << "-> downward(sqrt_e)(as(wxf))             = " << eve::downward(eve::sqrt_e)(eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> sqrt_e(as<wide_dt>())           = " << eve::sqrt_e(eve::as<wide_dt>())                << std::endl
            << "-> sqrt_e(as(wxd))                 = " << eve::sqrt_e(eve::as(wxd))                      << std::endl
            << "-> upward(sqrt_e)(as<wide_dt>())   = " << eve::upward(eve::sqrt_e)(eve::as<wide_dt>())   << std::endl
            << "-> upward(sqrt_e)(as(wxd))         = " << eve::upward(eve::sqrt_e)(eve::as(wxd))         << std::endl
            << "-> downward(sqrt_e)(as<wide_dt>()) = " << eve::downward(eve::sqrt_e)(eve::as<wide_dt>()) << std::endl
            << "-> downward(sqrt_e)(as(wxd))       = " << eve::downward(eve::sqrt_e)(eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> sqrt_e(as<float>())             = " << eve::sqrt_e(eve::as(float())) << std::endl
            << "-> sqrt_e(as<xf))                  = " << eve::sqrt_e(eve::as(xf))      << std::endl
            << "-> sqrt_e(as<double>())            = " << eve::sqrt_e(eve::as(double()))<< std::endl
            << "-> sqrt_e(as<xd))                  = " << eve::sqrt_e(eve::as(xd))      << std::endl;

  return 0;
}
