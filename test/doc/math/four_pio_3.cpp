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
            << "-> four_pio_3(as<wide_ft>())                 = " << eve::four_pio_3(eve::as<wide_ft>())                << std::endl
            << "-> four_pio_3(as(wxf))                       = " << eve::four_pio_3(eve::as(wxf))                      << std::endl
            << "-> upward(four_pio_3)(as<wide_ft>())         = " << eve::upward(eve::four_pio_3)(eve::as<wide_ft>())   << std::endl
            << "-> upward(four_pio_3)(as(wxf))               = " << eve::upward(eve::four_pio_3)(eve::as(wxf))         << std::endl
            << "-> downward(four_pio_3)(as<wide_ft>())       = " << eve::downward(eve::four_pio_3)(eve::as<wide_ft>()) << std::endl
            << "-> downward(four_pio_3)(as(wxf))             = " << eve::downward(eve::four_pio_3)(eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> four_pio_3(as<wide_dt>())           = " << eve::four_pio_3(eve::as<wide_dt>())                << std::endl
            << "-> four_pio_3(as(wxd))                 = " << eve::four_pio_3(eve::as(wxd))                      << std::endl
            << "-> upward(four_pio_3)(as<wide_dt>())   = " << eve::upward(eve::four_pio_3)(eve::as<wide_dt>())   << std::endl
            << "-> upward(four_pio_3)(as(wxd))         = " << eve::upward(eve::four_pio_3)(eve::as(wxd))         << std::endl
            << "-> downward(four_pio_3)(as<wide_dt>()) = " << eve::downward(eve::four_pio_3)(eve::as<wide_dt>()) << std::endl
            << "-> downward(four_pio_3)(as(wxd))       = " << eve::downward(eve::four_pio_3)(eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> four_pio_3(as<float>())             = " << eve::four_pio_3(eve::as(float())) << std::endl
            << "-> four_pio_3(as<xf))                  = " << eve::four_pio_3(eve::as(xf))      << std::endl
            << "-> four_pio_3(as<double>())            = " << eve::four_pio_3(eve::as(double()))<< std::endl
            << "-> four_pio_3(as<xd))                  = " << eve::four_pio_3(eve::as(xd))      << std::endl;

  return 0;
}
