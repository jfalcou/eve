#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;
using wide_dt = eve::wide<double>;

template<typename T>
consteval auto constexpr_inv_e() { return eve::inv_e(eve::as<T>{}); }

int main()
{
  wide_ft wxf;
  wide_dt wxd;

  std::cout << "---- simd"  << std::setprecision(9) << std::endl
            << "-> inv_e(as<wide_ft>())                 = " << eve::inv_e(eve::as<wide_ft>())                << std::endl
            << "-> inv_e(as(wxf))                       = " << eve::inv_e(eve::as(wxf))                      << std::endl
            << "-> inv_e[upward](as<wide_ft>())         = " << eve::inv_e[eve::upward](eve::as<wide_ft>())   << std::endl
            << "-> inv_e[upward](as(wxf))               = " << eve::inv_e[eve::upward](eve::as(wxf))         << std::endl
            << "-> inv_e[downward](as<wide_ft>())       = " << eve::inv_e[eve::downward](eve::as<wide_ft>()) << std::endl
            << "-> inv_e[downward](as(wxf))             = " << eve::inv_e[eve::downward](eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> inv_e(as<wide_dt>())           = " << eve::inv_e(eve::as<wide_dt>())                << std::endl
            << "-> inv_e(as(wxd))                 = " << eve::inv_e(eve::as(wxd))                      << std::endl
            << "-> inv_e[upward](as<wide_dt>())   = " << eve::inv_e[eve::upward](eve::as<wide_dt>())   << std::endl
            << "-> inv_e[upward](as(wxd))         = " << eve::inv_e[eve::upward](eve::as(wxd))         << std::endl
            << "-> inv_e[downward](as<wide_dt>()) = " << eve::inv_e[eve::downward](eve::as<wide_dt>()) << std::endl
            << "-> inv_e[downward](as(wxd))       = " << eve::inv_e[eve::downward](eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> inv_e(as<float>())             = " << eve::inv_e(eve::as(float())) << std::endl
            << "-> inv_e(as<xf))                  = " << eve::inv_e(eve::as(xf))      << std::endl
            << "-> inv_e(as<double>())            = " << eve::inv_e(eve::as(double()))<< std::endl
            << "-> inv_e(as<xd))                  = " << eve::inv_e(eve::as(xd))      << std::endl;


  std::cout << "-> constexpr inv_e            = " << constexpr_inv_e<float>() << std::endl;

  return 0;
}
