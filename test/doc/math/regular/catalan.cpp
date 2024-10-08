#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;
using wide_dt = eve::wide<double>;

template<typename T>
consteval auto constexpr_catalan() { return eve::catalan(eve::as<T>{}); }

int main()
{
  wide_ft wxf([](auto i, auto){return eve::is_odd(i)?-1.f:1.f; ; });
  wide_dt wxd;

  std::cout << "---- simd"  << std::setprecision(9) << std::endl
            << "-> catalan(as<wide_ft>())                 = " << eve::catalan(eve::as<wide_ft>())                << std::endl
            << "-> catalan(as(wxf))                       = " << eve::catalan(eve::as(wxf))                      << std::endl
            << "-> catalan[upper](as<wide_ft>())         = " << eve::catalan[eve::upper](eve::as<wide_ft>())   << std::endl
            << "-> catalan[upper](as(wxf))               = " << eve::catalan[eve::upper](eve::as(wxf))         << std::endl
            << "-> catalan[lower](as<wide_ft>())       = " << eve::catalan[eve::lower](eve::as<wide_ft>()) << std::endl
            << "-> catalan[lower](as(wxf))             = " << eve::catalan[eve::lower](eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> catalan(as<wide_dt>())           = " << eve::catalan(eve::as<wide_dt>())                << std::endl
            << "-> catalan(as(wxd))                 = " << eve::catalan(eve::as(wxd))                      << std::endl
            << "-> catalan[upper](as<wide_dt>())   = " << eve::catalan[eve::upper](eve::as<wide_dt>())   << std::endl
            << "-> catalan[upper](as(wxd))         = " << eve::catalan[eve::upper](eve::as(wxd))         << std::endl
            << "-> catalan[lower](as<wide_dt>()) = " << eve::catalan[eve::lower](eve::as<wide_dt>()) << std::endl
            << "-> catalan[lower](as(wxd))       = " << eve::catalan[eve::lower](eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> catalan(as<float>())             = " << eve::catalan(eve::as(float())) << std::endl
            << "-> catalan(as<xf))                  = " << eve::catalan(eve::as(xf))      << std::endl
            << "-> catalan(as<double>())            = " << eve::catalan(eve::as(double()))<< std::endl
            << "-> catalan(as<xd))                  = " << eve::catalan(eve::as(xd))      << std::endl;

   std::cout << "---- masked" << std::endl
             << "<- wxf                               = " << wxf << std::endl
             << "-> catalan[wxf <  0.0f](as(wxf))     = " << eve::catalan[wxf < 0.0f](eve::as(wxf)) << std::endl
             << "-> catalan[ignore_first(3)](as(wxf)) = " << eve::catalan[eve::ignore_first(3)](eve::as(wxf))  << std::endl;

   std::cout << "-> constexpr catalan                 = " << constexpr_catalan<float>() << std::endl;

  return 0;
}
