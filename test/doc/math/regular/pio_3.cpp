#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;
using wide_dt = eve::wide<double>;

template<typename T>
consteval auto constexpr_pio_3() { return eve::pio_3(eve::as<T>{}); }

int main()
{
  wide_ft wxf;
  wide_dt wxd;

  std::cout << "---- simd"  << std::setprecision(9) << std::endl
            << "-> pio_3(as<wide_ft>())                 = " << eve::pio_3(eve::as<wide_ft>())                << std::endl
            << "-> pio_3(as(wxf))                       = " << eve::pio_3(eve::as(wxf))                      << std::endl
            << "-> pio_3[upper](as<wide_ft>())         = " << eve::pio_3[eve::upper](eve::as<wide_ft>())   << std::endl
            << "-> pio_3[upper](as(wxf))               = " << eve::pio_3[eve::upper](eve::as(wxf))         << std::endl
            << "-> pio_3[lower](as<wide_ft>())       = " << eve::pio_3[eve::lower](eve::as<wide_ft>()) << std::endl
            << "-> pio_3[lower](as(wxf))             = " << eve::pio_3[eve::lower](eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> pio_3(as<wide_dt>())           = " << eve::pio_3(eve::as<wide_dt>())                << std::endl
            << "-> pio_3(as(wxd))                 = " << eve::pio_3(eve::as(wxd))                      << std::endl
            << "-> pio_3[upper](as<wide_dt>())   = " << eve::pio_3[eve::upper](eve::as<wide_dt>())   << std::endl
            << "-> pio_3[upper](as(wxd))         = " << eve::pio_3[eve::upper](eve::as(wxd))         << std::endl
            << "-> pio_3[lower](as<wide_dt>()) = " << eve::pio_3[eve::lower](eve::as<wide_dt>()) << std::endl
            << "-> pio_3[lower](as(wxd))       = " << eve::pio_3[eve::lower](eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> pio_3(as<float>())             = " << eve::pio_3(eve::as(float())) << std::endl
            << "-> pio_3(as<xf))                  = " << eve::pio_3(eve::as(xf))      << std::endl
            << "-> pio_3(as<double>())            = " << eve::pio_3(eve::as(double()))<< std::endl
            << "-> pio_3(as<xd))                  = " << eve::pio_3(eve::as(xd))      << std::endl;


  std::cout << "-> constexpr pio_3            = " << constexpr_pio_3<float>() << std::endl;

  return 0;
}
