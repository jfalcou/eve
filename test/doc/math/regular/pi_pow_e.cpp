#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;
using wide_dt = eve::wide<double>;

template<typename T>
consteval auto constexpr_pi_pow_e() { return eve::pi_pow_e(eve::as<T>{}); }

int main()
{
  wide_ft wxf;
  wide_dt wxd;

  std::cout << "---- simd"  << std::setprecision(9) << std::endl
            << "-> pi_pow_e(as<wide_ft>())                 = " << eve::pi_pow_e(eve::as<wide_ft>())                << std::endl
            << "-> pi_pow_e(as(wxf))                       = " << eve::pi_pow_e(eve::as(wxf))                      << std::endl
            << "-> pi_pow_e[upward](as<wide_ft>())         = " << eve::pi_pow_e[eve::upward](eve::as<wide_ft>())   << std::endl
            << "-> pi_pow_e[upward](as(wxf))               = " << eve::pi_pow_e[eve::upward](eve::as(wxf))         << std::endl
            << "-> pi_pow_e[downward](as<wide_ft>())       = " << eve::pi_pow_e[eve::downward](eve::as<wide_ft>()) << std::endl
            << "-> pi_pow_e[downward](as(wxf))             = " << eve::pi_pow_e[eve::downward](eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> pi_pow_e(as<wide_dt>())           = " << eve::pi_pow_e(eve::as<wide_dt>())                << std::endl
            << "-> pi_pow_e(as(wxd))                 = " << eve::pi_pow_e(eve::as(wxd))                      << std::endl
            << "-> pi_pow_e[upward](as<wide_dt>())   = " << eve::pi_pow_e[eve::upward](eve::as<wide_dt>())   << std::endl
            << "-> pi_pow_e[upward](as(wxd))         = " << eve::pi_pow_e[eve::upward](eve::as(wxd))         << std::endl
            << "-> pi_pow_e[downward](as<wide_dt>()) = " << eve::pi_pow_e[eve::downward](eve::as<wide_dt>()) << std::endl
            << "-> pi_pow_e[downward](as(wxd))       = " << eve::pi_pow_e[eve::downward](eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> pi_pow_e(as<float>())             = " << eve::pi_pow_e(eve::as(float())) << std::endl
            << "-> pi_pow_e(as<xf))                  = " << eve::pi_pow_e(eve::as(xf))      << std::endl
            << "-> pi_pow_e(as<double>())            = " << eve::pi_pow_e(eve::as(double()))<< std::endl
            << "-> pi_pow_e(as<xd))                  = " << eve::pi_pow_e(eve::as(xd))      << std::endl;


  std::cout << "-> constexpr pi_pow_e            = " << constexpr_pi_pow_e<float>() << std::endl;

  return 0;
}
