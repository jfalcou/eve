#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;
using wide_dt = eve::wide<double>;

template<typename T>
consteval auto constexpr_three_pio_4() { return eve::three_pio_4(eve::as<T>{}); }

int main()
{
  wide_ft wxf;
  wide_dt wxd;

  std::cout << "---- simd"  << std::setprecision(9) << std::endl
            << "-> three_pio_4(as<wide_ft>())                 = " << eve::three_pio_4(eve::as<wide_ft>())                << std::endl
            << "-> three_pio_4(as(wxf))                       = " << eve::three_pio_4(eve::as(wxf))                      << std::endl
            << "-> three_pio_4[upward](as<wide_ft>())         = " << eve::three_pio_4[eve::upward](eve::as<wide_ft>())   << std::endl
            << "-> three_pio_4[upward](as(wxf))               = " << eve::three_pio_4[eve::upward](eve::as(wxf))         << std::endl
            << "-> three_pio_4[downward](as<wide_ft>())       = " << eve::three_pio_4[eve::downward](eve::as<wide_ft>()) << std::endl
            << "-> three_pio_4[downward](as(wxf))             = " << eve::three_pio_4[eve::downward](eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> three_pio_4(as<wide_dt>())           = " << eve::three_pio_4(eve::as<wide_dt>())                << std::endl
            << "-> three_pio_4(as(wxd))                 = " << eve::three_pio_4(eve::as(wxd))                      << std::endl
            << "-> three_pio_4[upward](as<wide_dt>())   = " << eve::three_pio_4[eve::upward](eve::as<wide_dt>())   << std::endl
            << "-> three_pio_4[upward](as(wxd))         = " << eve::three_pio_4[eve::upward](eve::as(wxd))         << std::endl
            << "-> three_pio_4[downward](as<wide_dt>()) = " << eve::three_pio_4[eve::downward](eve::as<wide_dt>()) << std::endl
            << "-> three_pio_4[downward](as(wxd))       = " << eve::three_pio_4[eve::downward](eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> three_pio_4(as<float>())             = " << eve::three_pio_4(eve::as(float())) << std::endl
            << "-> three_pio_4(as<xf))                  = " << eve::three_pio_4(eve::as(xf))      << std::endl
            << "-> three_pio_4(as<double>())            = " << eve::three_pio_4(eve::as(double()))<< std::endl
            << "-> three_pio_4(as<xd))                  = " << eve::three_pio_4(eve::as(xd))      << std::endl;


  std::cout << "-> constexpr three_pio_4            = " << constexpr_three_pio_4<float>() << std::endl;

  return 0;
}
