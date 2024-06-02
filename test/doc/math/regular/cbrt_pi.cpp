#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;
using wide_dt = eve::wide<double>;

template<typename T>
consteval auto constexpr_cbrt_pi() { return eve::cbrt_pi(eve::as<T>{}); }

int main()
{
  wide_ft wxf;
  wide_dt wxd;

  std::cout << "---- simd"  << std::setprecision(9) << std::endl
            << "-> cbrt_pi(as<wide_ft>())                 = " << eve::cbrt_pi(eve::as<wide_ft>())                << std::endl
            << "-> cbrt_pi(as(wxf))                       = " << eve::cbrt_pi(eve::as(wxf))                      << std::endl
            << "-> cbrt_pi[upward](as<wide_ft>())         = " << eve::cbrt_pi[eve::upward](eve::as<wide_ft>())   << std::endl
            << "-> cbrt_pi[upward](as(wxf))               = " << eve::cbrt_pi[eve::upward](eve::as(wxf))         << std::endl
            << "-> cbrt_pi[downward](as<wide_ft>())       = " << eve::cbrt_pi[eve::downward](eve::as<wide_ft>()) << std::endl
            << "-> cbrt_pi[downward](as(wxf))             = " << eve::cbrt_pi[eve::downward](eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> cbrt_pi(as<wide_dt>())           = " << eve::cbrt_pi(eve::as<wide_dt>())                << std::endl
            << "-> cbrt_pi(as(wxd))                 = " << eve::cbrt_pi(eve::as(wxd))                      << std::endl
            << "-> cbrt_pi[upward](as<wide_dt>())   = " << eve::cbrt_pi[eve::upward](eve::as<wide_dt>())   << std::endl
            << "-> cbrt_pi[upward](as(wxd))         = " << eve::cbrt_pi[eve::upward](eve::as(wxd))         << std::endl
            << "-> cbrt_pi[downward](as<wide_dt>()) = " << eve::cbrt_pi[eve::downward](eve::as<wide_dt>()) << std::endl
            << "-> cbrt_pi[downward](as(wxd))       = " << eve::cbrt_pi[eve::downward](eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> cbrt_pi(as<float>())             = " << eve::cbrt_pi(eve::as(float())) << std::endl
            << "-> cbrt_pi(as<xf))                  = " << eve::cbrt_pi(eve::as(xf))      << std::endl
            << "-> cbrt_pi(as<double>())            = " << eve::cbrt_pi(eve::as(double()))<< std::endl
            << "-> cbrt_pi(as<xd))                  = " << eve::cbrt_pi(eve::as(xd))      << std::endl;


  std::cout << "-> constexpr cbrt_pi            = " << constexpr_cbrt_pi<float>() << std::endl;

  return 0;
}
