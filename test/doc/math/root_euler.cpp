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
            << "-> root_euler(as<wide_ft>())                 = " << eve::root_euler(eve::as<wide_ft>())                << std::endl
            << "-> root_euler(as(wxf))                       = " << eve::root_euler(eve::as(wxf))                      << std::endl
            << "-> upward(root_euler)(as<wide_ft>())         = " << eve::upward(eve::root_euler)(eve::as<wide_ft>())   << std::endl
            << "-> upward(root_euler)(as(wxf))               = " << eve::upward(eve::root_euler)(eve::as(wxf))         << std::endl
            << "-> downward(root_euler)(as<wide_ft>())       = " << eve::downward(eve::root_euler)(eve::as<wide_ft>()) << std::endl
            << "-> downward(root_euler)(as(wxf))             = " << eve::downward(eve::root_euler)(eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> root_euler(as<wide_dt>())           = " << eve::root_euler(eve::as<wide_dt>())                << std::endl
            << "-> root_euler(as(wxd))                 = " << eve::root_euler(eve::as(wxd))                      << std::endl
            << "-> upward(root_euler)(as<wide_dt>())   = " << eve::upward(eve::root_euler)(eve::as<wide_dt>())   << std::endl
            << "-> upward(root_euler)(as(wxd))         = " << eve::upward(eve::root_euler)(eve::as(wxd))         << std::endl
            << "-> downward(root_euler)(as<wide_dt>()) = " << eve::downward(eve::root_euler)(eve::as<wide_dt>()) << std::endl
            << "-> downward(root_euler)(as(wxd))       = " << eve::downward(eve::root_euler)(eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> root_euler(as<float>())             = " << eve::root_euler(eve::as(float())) << std::endl
            << "-> root_euler(as<xf))                  = " << eve::root_euler(eve::as(xf))      << std::endl
            << "-> root_euler(as<double>())            = " << eve::root_euler(eve::as(double()))<< std::endl
            << "-> root_euler(as<xd))                  = " << eve::root_euler(eve::as(xd))      << std::endl;

  return 0;
}
