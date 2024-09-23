#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;
using wide_dt = eve::wide<double>;

template<typename T>
consteval auto constexpr_sqrt_pio_2() { return eve::sqrt_pio_2(eve::as<T>{}); }

int main()
{
  wide_ft wxf;
  wide_dt wxd;

  std::cout << "---- simd"  << std::setprecision(9) << std::endl
            << "-> sqrt_pio_2(as<wide_ft>())                 = " << eve::sqrt_pio_2(eve::as<wide_ft>())                << std::endl
            << "-> sqrt_pio_2(as(wxf))                       = " << eve::sqrt_pio_2(eve::as(wxf))                      << std::endl
            << "-> sqrt_pio_2[upper](as<wide_ft>())         = " << eve::sqrt_pio_2[eve::upper](eve::as<wide_ft>())   << std::endl
            << "-> sqrt_pio_2[upper](as(wxf))               = " << eve::sqrt_pio_2[eve::upper](eve::as(wxf))         << std::endl
            << "-> sqrt_pio_2[lower](as<wide_ft>())       = " << eve::sqrt_pio_2[eve::lower](eve::as<wide_ft>()) << std::endl
            << "-> sqrt_pio_2[lower](as(wxf))             = " << eve::sqrt_pio_2[eve::lower](eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> sqrt_pio_2(as<wide_dt>())           = " << eve::sqrt_pio_2(eve::as<wide_dt>())                << std::endl
            << "-> sqrt_pio_2(as(wxd))                 = " << eve::sqrt_pio_2(eve::as(wxd))                      << std::endl
            << "-> sqrt_pio_2[upper](as<wide_dt>())   = " << eve::sqrt_pio_2[eve::upper](eve::as<wide_dt>())   << std::endl
            << "-> sqrt_pio_2[upper](as(wxd))         = " << eve::sqrt_pio_2[eve::upper](eve::as(wxd))         << std::endl
            << "-> sqrt_pio_2[lower](as<wide_dt>()) = " << eve::sqrt_pio_2[eve::lower](eve::as<wide_dt>()) << std::endl
            << "-> sqrt_pio_2[lower](as(wxd))       = " << eve::sqrt_pio_2[eve::lower](eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> sqrt_pio_2(as<float>())             = " << eve::sqrt_pio_2(eve::as(float())) << std::endl
            << "-> sqrt_pio_2(as<xf))                  = " << eve::sqrt_pio_2(eve::as(xf))      << std::endl
            << "-> sqrt_pio_2(as<double>())            = " << eve::sqrt_pio_2(eve::as(double()))<< std::endl
            << "-> sqrt_pio_2(as<xd))                  = " << eve::sqrt_pio_2(eve::as(xd))      << std::endl;


  std::cout << "-> constexpr sqrt_pio_2            = " << constexpr_sqrt_pio_2<float>() << std::endl;

  return 0;
}
