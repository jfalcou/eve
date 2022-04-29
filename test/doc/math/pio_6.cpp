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
            << "-> pio_6(as<wide_ft>())                 = " << eve::pio_6(eve::as<wide_ft>())                << std::endl
            << "-> pio_6(as(wxf))                       = " << eve::pio_6(eve::as(wxf))                      << std::endl
            << "-> upward(pio_6)(as<wide_ft>())         = " << eve::upward(eve::pio_6)(eve::as<wide_ft>())   << std::endl
            << "-> upward(pio_6)(as(wxf))               = " << eve::upward(eve::pio_6)(eve::as(wxf))         << std::endl
            << "-> downward(pio_6)(as<wide_ft>())       = " << eve::downward(eve::pio_6)(eve::as<wide_ft>()) << std::endl
            << "-> downward(pio_6)(as(wxf))             = " << eve::downward(eve::pio_6)(eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> pio_6(as<wide_dt>())           = " << eve::pio_6(eve::as<wide_dt>())                << std::endl
            << "-> pio_6(as(wxd))                 = " << eve::pio_6(eve::as(wxd))                      << std::endl
            << "-> upward(pio_6)(as<wide_dt>())   = " << eve::upward(eve::pio_6)(eve::as<wide_dt>())   << std::endl
            << "-> upward(pio_6)(as(wxd))         = " << eve::upward(eve::pio_6)(eve::as(wxd))         << std::endl
            << "-> downward(pio_6)(as<wide_dt>()) = " << eve::downward(eve::pio_6)(eve::as<wide_dt>()) << std::endl
            << "-> downward(pio_6)(as(wxd))       = " << eve::downward(eve::pio_6)(eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> pio_6(as<float>())             = " << eve::pio_6(eve::as(float())) << std::endl
            << "-> pio_6(as<xf))                  = " << eve::pio_6(eve::as(xf))      << std::endl
            << "-> pio_6(as<double>())            = " << eve::pio_6(eve::as(double()))<< std::endl
            << "-> pio_6(as<xd))                  = " << eve::pio_6(eve::as(xd))      << std::endl;

  return 0;
}
