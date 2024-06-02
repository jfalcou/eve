#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;
using wide_dt = eve::wide<double>;

template<typename T>
consteval auto constexpr_pio_6() { return eve::pio_6(eve::as<T>{}); }

int main()
{
  wide_ft wxf;
  wide_dt wxd;

  std::cout << "---- simd"  << std::setprecision(9) << std::endl
            << "-> pio_6(as<wide_ft>())                 = " << eve::pio_6(eve::as<wide_ft>())                << std::endl
            << "-> pio_6(as(wxf))                       = " << eve::pio_6(eve::as(wxf))                      << std::endl
            << "-> pio_6[upward](as<wide_ft>())         = " << eve::pio_6[eve::upward](eve::as<wide_ft>())   << std::endl
            << "-> pio_6[upward](as(wxf))               = " << eve::pio_6[eve::upward](eve::as(wxf))         << std::endl
            << "-> pio_6[downward](as<wide_ft>())       = " << eve::pio_6[eve::downward](eve::as<wide_ft>()) << std::endl
            << "-> pio_6[downward](as(wxf))             = " << eve::pio_6[eve::downward](eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> pio_6(as<wide_dt>())           = " << eve::pio_6(eve::as<wide_dt>())                << std::endl
            << "-> pio_6(as(wxd))                 = " << eve::pio_6(eve::as(wxd))                      << std::endl
            << "-> pio_6[upward](as<wide_dt>())   = " << eve::pio_6[eve::upward](eve::as<wide_dt>())   << std::endl
            << "-> pio_6[upward](as(wxd))         = " << eve::pio_6[eve::upward](eve::as(wxd))         << std::endl
            << "-> pio_6[downward](as<wide_dt>()) = " << eve::pio_6[eve::downward](eve::as<wide_dt>()) << std::endl
            << "-> pio_6[downward](as(wxd))       = " << eve::pio_6[eve::downward](eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> pio_6(as<float>())             = " << eve::pio_6(eve::as(float())) << std::endl
            << "-> pio_6(as<xf))                  = " << eve::pio_6(eve::as(xf))      << std::endl
            << "-> pio_6(as<double>())            = " << eve::pio_6(eve::as(double()))<< std::endl
            << "-> pio_6(as<xd))                  = " << eve::pio_6(eve::as(xd))      << std::endl;


  std::cout << "-> constexpr pio_6            = " << constexpr_pio_6<float>() << std::endl;

  return 0;
}
