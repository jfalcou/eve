#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;
using wide_dt = eve::wide<double>;

template<typename T>
consteval auto constexpr_sqrt_3() { return eve::sqrt_3(eve::as<T>{}); }

int main()
{
  wide_ft wxf;
  wide_dt wxd;

  std::cout << "---- simd"  << std::setprecision(9) << std::endl
            << "-> sqrt_3(as<wide_ft>())                 = " << eve::sqrt_3(eve::as<wide_ft>())                << std::endl
            << "-> sqrt_3(as(wxf))                       = " << eve::sqrt_3(eve::as(wxf))                      << std::endl
            << "-> sqrt_3[upward](as<wide_ft>())         = " << eve::sqrt_3[eve::upward](eve::as<wide_ft>())   << std::endl
            << "-> sqrt_3[upward](as(wxf))               = " << eve::sqrt_3[eve::upward](eve::as(wxf))         << std::endl
            << "-> sqrt_3[downward](as<wide_ft>())       = " << eve::sqrt_3[eve::downward](eve::as<wide_ft>()) << std::endl
            << "-> sqrt_3[downward](as(wxf))             = " << eve::sqrt_3[eve::downward](eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> sqrt_3(as<wide_dt>())           = " << eve::sqrt_3(eve::as<wide_dt>())                << std::endl
            << "-> sqrt_3(as(wxd))                 = " << eve::sqrt_3(eve::as(wxd))                      << std::endl
            << "-> sqrt_3[upward](as<wide_dt>())   = " << eve::sqrt_3[eve::upward](eve::as<wide_dt>())   << std::endl
            << "-> sqrt_3[upward](as(wxd))         = " << eve::sqrt_3[eve::upward](eve::as(wxd))         << std::endl
            << "-> sqrt_3[downward](as<wide_dt>()) = " << eve::sqrt_3[eve::downward](eve::as<wide_dt>()) << std::endl
            << "-> sqrt_3[downward](as(wxd))       = " << eve::sqrt_3[eve::downward](eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> sqrt_3(as<float>())             = " << eve::sqrt_3(eve::as(float())) << std::endl
            << "-> sqrt_3(as<xf))                  = " << eve::sqrt_3(eve::as(xf))      << std::endl
            << "-> sqrt_3(as<double>())            = " << eve::sqrt_3(eve::as(double()))<< std::endl
            << "-> sqrt_3(as<xd))                  = " << eve::sqrt_3(eve::as(xd))      << std::endl;


  std::cout << "-> constexpr sqrt_3            = " << constexpr_sqrt_3<float>() << std::endl;

  return 0;
}
