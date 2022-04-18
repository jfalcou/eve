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
            << "-> glaisher(as<wide_ft>())                 = " << eve::glaisher(eve::as<wide_ft>())                << std::endl
            << "-> glaisher(as(wxf))                       = " << eve::glaisher(eve::as(wxf))                      << std::endl
            << "-> upward(glaisher)(as<wide_ft>())         = " << eve::upward(eve::glaisher)(eve::as<wide_ft>())   << std::endl
            << "-> upward(glaisher)(as(wxf))               = " << eve::upward(eve::glaisher)(eve::as(wxf))         << std::endl
            << "-> downward(glaisher)(as<wide_ft>())       = " << eve::downward(eve::glaisher)(eve::as<wide_ft>()) << std::endl
            << "-> downward(glaisher)(as(wxf))             = " << eve::downward(eve::glaisher)(eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> glaisher(as<wide_dt>())           = " << eve::glaisher(eve::as<wide_dt>())                << std::endl
            << "-> glaisher(as(wxd))                 = " << eve::glaisher(eve::as(wxd))                      << std::endl
            << "-> upward(glaisher)(as<wide_dt>())   = " << eve::upward(eve::glaisher)(eve::as<wide_dt>())   << std::endl
            << "-> upward(glaisher)(as(wxd))         = " << eve::upward(eve::glaisher)(eve::as(wxd))         << std::endl
            << "-> downward(glaisher)(as<wide_dt>()) = " << eve::downward(eve::glaisher)(eve::as<wide_dt>()) << std::endl
            << "-> downward(glaisher)(as(wxd))       = " << eve::downward(eve::glaisher)(eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> glaisher(as<float>())             = " << eve::glaisher(eve::as(float())) << std::endl
            << "-> glaisher(as<xf))                  = " << eve::glaisher(eve::as(xf))      << std::endl
            << "-> glaisher(as<double>())            = " << eve::glaisher(eve::as(double()))<< std::endl
            << "-> glaisher(as<xd))                  = " << eve::glaisher(eve::as(xd))      << std::endl;

  return 0;
}
