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
            << "-> inv_root_two(as<wide_ft>())                 = " << eve::inv_root_two(eve::as<wide_ft>())                << std::endl
            << "-> inv_root_two(as(wxf))                       = " << eve::inv_root_two(eve::as(wxf))                      << std::endl
            << "-> upward(inv_root_two)(as<wide_ft>())         = " << eve::upward(eve::inv_root_two)(eve::as<wide_ft>())   << std::endl
            << "-> upward(inv_root_two)(as(wxf))               = " << eve::upward(eve::inv_root_two)(eve::as(wxf))         << std::endl
            << "-> downward(inv_root_two)(as<wide_ft>())       = " << eve::downward(eve::inv_root_two)(eve::as<wide_ft>()) << std::endl
            << "-> downward(inv_root_two)(as(wxf))             = " << eve::downward(eve::inv_root_two)(eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> inv_root_two(as<wide_dt>())           = " << eve::inv_root_two(eve::as<wide_dt>())                << std::endl
            << "-> inv_root_two(as(wxd))                 = " << eve::inv_root_two(eve::as(wxd))                      << std::endl
            << "-> upward(inv_root_two)(as<wide_dt>())   = " << eve::upward(eve::inv_root_two)(eve::as<wide_dt>())   << std::endl
            << "-> upward(inv_root_two)(as(wxd))         = " << eve::upward(eve::inv_root_two)(eve::as(wxd))         << std::endl
            << "-> downward(inv_root_two)(as<wide_dt>()) = " << eve::downward(eve::inv_root_two)(eve::as<wide_dt>()) << std::endl
            << "-> downward(inv_root_two)(as(wxd))       = " << eve::downward(eve::inv_root_two)(eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> inv_root_two(as<float>())             = " << eve::inv_root_two(eve::as(float())) << std::endl
            << "-> inv_root_two(as<xf))                  = " << eve::inv_root_two(eve::as(xf))      << std::endl
            << "-> inv_root_two(as<double>())            = " << eve::inv_root_two(eve::as(double()))<< std::endl
            << "-> inv_root_two(as<xd))                  = " << eve::inv_root_two(eve::as(xd))      << std::endl;

  return 0;
}
