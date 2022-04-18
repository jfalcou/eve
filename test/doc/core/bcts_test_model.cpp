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
            << "-> name_zz(as<wide_ft>())                 = " << eve::name_zz(eve::as<wide_ft>())                << std::endl
            << "-> name_zz(as(wxf))                       = " << eve::name_zz(eve::as(wxf))                      << std::endl
            << "-> upward(name_zz)(as<wide_ft>())         = " << eve::upward(eve::name_zz)(eve::as<wide_ft>())   << std::endl
            << "-> upward(name_zz)(as(wxf))               = " << eve::upward(eve::name_zz)(eve::as(wxf))         << std::endl
            << "-> downward(name_zz)(as<wide_ft>())       = " << eve::downward(eve::name_zz)(eve::as<wide_ft>()) << std::endl
            << "-> downward(name_zz)(as(wxf))             = " << eve::downward(eve::name_zz)(eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> name_zz(as<wide_dt>())           = " << eve::name_zz(eve::as<wide_dt>())                << std::endl
            << "-> name_zz(as(wxd))                 = " << eve::name_zz(eve::as(wxd))                      << std::endl
            << "-> upward(name_zz)(as<wide_dt>())   = " << eve::upward(eve::name_zz)(eve::as<wide_dt>())   << std::endl
            << "-> upward(name_zz)(as(wxd))         = " << eve::upward(eve::name_zz)(eve::as(wxd))         << std::endl
            << "-> downward(name_zz)(as<wide_dt>()) = " << eve::downward(eve::name_zz)(eve::as<wide_dt>()) << std::endl
            << "-> downward(name_zz)(as(wxd))       = " << eve::downward(eve::name_zz)(eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> name_zz(as<float>())             = " << eve::name_zz(eve::as(float())) << std::endl
            << "-> name_zz(as<xf))                  = " << eve::name_zz(eve::as(xf))      << std::endl
            << "-> name_zz(as<double>())            = " << eve::name_zz(eve::as(double()))<< std::endl
            << "-> name_zz(as<xd))                  = " << eve::name_zz(eve::as(xd))      << std::endl;

  return 0;
}
