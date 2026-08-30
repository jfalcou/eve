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
            << "-> cbrt_pi[upper](as<wide_ft>())         = " << eve::cbrt_pi[eve::upper](eve::as<wide_ft>())   << std::endl
            << "-> cbrt_pi[upper](as(wxf))               = " << eve::cbrt_pi[eve::upper](eve::as(wxf))         << std::endl
            << "-> cbrt_pi[lower](as<wide_ft>())       = " << eve::cbrt_pi[eve::lower](eve::as<wide_ft>()) << std::endl
            << "-> cbrt_pi[lower](as(wxf))             = " << eve::cbrt_pi[eve::lower](eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> cbrt_pi(as<wide_dt>())           = " << eve::cbrt_pi(eve::as<wide_dt>())                << std::endl
            << "-> cbrt_pi(as(wxd))                 = " << eve::cbrt_pi(eve::as(wxd))                      << std::endl
            << "-> cbrt_pi[upper](as<wide_dt>())   = " << eve::cbrt_pi[eve::upper](eve::as<wide_dt>())   << std::endl
            << "-> cbrt_pi[upper](as(wxd))         = " << eve::cbrt_pi[eve::upper](eve::as(wxd))         << std::endl
            << "-> cbrt_pi[lower](as<wide_dt>()) = " << eve::cbrt_pi[eve::lower](eve::as<wide_dt>()) << std::endl
            << "-> cbrt_pi[lower](as(wxd))       = " << eve::cbrt_pi[eve::lower](eve::as(wxd))       << std::endl;

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
