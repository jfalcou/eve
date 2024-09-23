#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;
using wide_dt = eve::wide<double>;

template<typename T>
consteval auto constexpr_sqrt_e() { return eve::sqrt_e(eve::as<T>{}); }

int main()
{
  wide_ft wxf;
  wide_dt wxd;

  std::cout << "---- simd"  << std::setprecision(9) << std::endl
            << "-> sqrt_e(as<wide_ft>())                 = " << eve::sqrt_e(eve::as<wide_ft>())                << std::endl
            << "-> sqrt_e(as(wxf))                       = " << eve::sqrt_e(eve::as(wxf))                      << std::endl
            << "-> sqrt_e[upper](as<wide_ft>())         = " << eve::sqrt_e[eve::upper](eve::as<wide_ft>())   << std::endl
            << "-> sqrt_e[upper](as(wxf))               = " << eve::sqrt_e[eve::upper](eve::as(wxf))         << std::endl
            << "-> sqrt_e[lower](as<wide_ft>())       = " << eve::sqrt_e[eve::lower](eve::as<wide_ft>()) << std::endl
            << "-> sqrt_e[lower](as(wxf))             = " << eve::sqrt_e[eve::lower](eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> sqrt_e(as<wide_dt>())           = " << eve::sqrt_e(eve::as<wide_dt>())                << std::endl
            << "-> sqrt_e(as(wxd))                 = " << eve::sqrt_e(eve::as(wxd))                      << std::endl
            << "-> sqrt_e[upper](as<wide_dt>())   = " << eve::sqrt_e[eve::upper](eve::as<wide_dt>())   << std::endl
            << "-> sqrt_e[upper](as(wxd))         = " << eve::sqrt_e[eve::upper](eve::as(wxd))         << std::endl
            << "-> sqrt_e[lower](as<wide_dt>()) = " << eve::sqrt_e[eve::lower](eve::as<wide_dt>()) << std::endl
            << "-> sqrt_e[lower](as(wxd))       = " << eve::sqrt_e[eve::lower](eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> sqrt_e(as<float>())             = " << eve::sqrt_e(eve::as(float())) << std::endl
            << "-> sqrt_e(as<xf))                  = " << eve::sqrt_e(eve::as(xf))      << std::endl
            << "-> sqrt_e(as<double>())            = " << eve::sqrt_e(eve::as(double()))<< std::endl
            << "-> sqrt_e(as<xd))                  = " << eve::sqrt_e(eve::as(xd))      << std::endl;


  std::cout << "-> constexpr sqrt_e            = " << constexpr_sqrt_e<float>() << std::endl;

  return 0;
}
