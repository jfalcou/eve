#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;
using wide_dt = eve::wide<double>;

template<typename T>
consteval auto constexpr_pi2() { return eve::pi2(eve::as<T>{}); }

int main()
{
  wide_ft wxf;
  wide_dt wxd;

  std::cout << "---- simd"  << std::setprecision(9) << std::endl
            << "-> pi2(as<wide_ft>())                 = " << eve::pi2(eve::as<wide_ft>())                << std::endl
            << "-> pi2(as(wxf))                       = " << eve::pi2(eve::as(wxf))                      << std::endl
            << "-> pi2[upward](as<wide_ft>())         = " << eve::pi2[eve::upward](eve::as<wide_ft>())   << std::endl
            << "-> pi2[upward](as(wxf))               = " << eve::pi2[eve::upward](eve::as(wxf))         << std::endl
            << "-> pi2[downward](as<wide_ft>())       = " << eve::pi2[eve::downward](eve::as<wide_ft>()) << std::endl
            << "-> pi2[downward](as(wxf))             = " << eve::pi2[eve::downward](eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> pi2(as<wide_dt>())           = " << eve::pi2(eve::as<wide_dt>())                << std::endl
            << "-> pi2(as(wxd))                 = " << eve::pi2(eve::as(wxd))                      << std::endl
            << "-> pi2[upward](as<wide_dt>())   = " << eve::pi2[eve::upward](eve::as<wide_dt>())   << std::endl
            << "-> pi2[upward](as(wxd))         = " << eve::pi2[eve::upward](eve::as(wxd))         << std::endl
            << "-> pi2[downward](as<wide_dt>()) = " << eve::pi2[eve::downward](eve::as<wide_dt>()) << std::endl
            << "-> pi2[downward](as(wxd))       = " << eve::pi2[eve::downward](eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> pi2(as<float>())             = " << eve::pi2(eve::as(float())) << std::endl
            << "-> pi2(as<xf))                  = " << eve::pi2(eve::as(xf))      << std::endl
            << "-> pi2(as<double>())            = " << eve::pi2(eve::as(double()))<< std::endl
            << "-> pi2(as<xd))                  = " << eve::pi2(eve::as(xd))      << std::endl;


  std::cout << "-> constexpr pi2            = " << constexpr_pi2<float>() << std::endl;

  return 0;
}
