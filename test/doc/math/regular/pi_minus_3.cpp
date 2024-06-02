#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;
using wide_dt = eve::wide<double>;

template<typename T>
consteval auto constexpr_pi_minus_3() { return eve::pi_minus_3(eve::as<T>{}); }

int main()
{
  wide_ft wxf;
  wide_dt wxd;

  std::cout << "---- simd"  << std::setprecision(9) << std::endl
            << "-> pi_minus_3(as<wide_ft>())                 = " << eve::pi_minus_3(eve::as<wide_ft>())                << std::endl
            << "-> pi_minus_3(as(wxf))                       = " << eve::pi_minus_3(eve::as(wxf))                      << std::endl
            << "-> pi_minus_3[upward](as<wide_ft>())         = " << eve::pi_minus_3[eve::upward](eve::as<wide_ft>())   << std::endl
            << "-> pi_minus_3[upward](as(wxf))               = " << eve::pi_minus_3[eve::upward](eve::as(wxf))         << std::endl
            << "-> pi_minus_3[downward](as<wide_ft>())       = " << eve::pi_minus_3[eve::downward](eve::as<wide_ft>()) << std::endl
            << "-> pi_minus_3[downward](as(wxf))             = " << eve::pi_minus_3[eve::downward](eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> pi_minus_3(as<wide_dt>())           = " << eve::pi_minus_3(eve::as<wide_dt>())                << std::endl
            << "-> pi_minus_3(as(wxd))                 = " << eve::pi_minus_3(eve::as(wxd))                      << std::endl
            << "-> pi_minus_3[upward](as<wide_dt>())   = " << eve::pi_minus_3[eve::upward](eve::as<wide_dt>())   << std::endl
            << "-> pi_minus_3[upward](as(wxd))         = " << eve::pi_minus_3[eve::upward](eve::as(wxd))         << std::endl
            << "-> pi_minus_3[downward](as<wide_dt>()) = " << eve::pi_minus_3[eve::downward](eve::as<wide_dt>()) << std::endl
            << "-> pi_minus_3[downward](as(wxd))       = " << eve::pi_minus_3[eve::downward](eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> pi_minus_3(as<float>())             = " << eve::pi_minus_3(eve::as(float())) << std::endl
            << "-> pi_minus_3(as<xf))                  = " << eve::pi_minus_3(eve::as(xf))      << std::endl
            << "-> pi_minus_3(as<double>())            = " << eve::pi_minus_3(eve::as(double()))<< std::endl
            << "-> pi_minus_3(as<xd))                  = " << eve::pi_minus_3(eve::as(xd))      << std::endl;


  std::cout << "-> constexpr pi_minus_3            = " << constexpr_pi_minus_3<float>() << std::endl;

  return 0;
}
