#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;
using wide_dt = eve::wide<double>;

template<typename T>
consteval auto constexpr_glaisher() { return eve::glaisher(eve::as<T>{}); }

int main()
{
  wide_ft wxf;
  wide_dt wxd;

  std::cout << "---- simd"  << std::setprecision(9) << std::endl
            << "-> glaisher(as<wide_ft>())                 = " << eve::glaisher(eve::as<wide_ft>())                << std::endl
            << "-> glaisher(as(wxf))                       = " << eve::glaisher(eve::as(wxf))                      << std::endl
            << "-> glaisher[upward](as<wide_ft>())         = " << eve::glaisher[eve::upward](eve::as<wide_ft>())   << std::endl
            << "-> glaisher[upward](as(wxf))               = " << eve::glaisher[eve::upward](eve::as(wxf))         << std::endl
            << "-> glaisher[downward](as<wide_ft>())       = " << eve::glaisher[eve::downward](eve::as<wide_ft>()) << std::endl
            << "-> glaisher[downward](as(wxf))             = " << eve::glaisher[eve::downward](eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> glaisher(as<wide_dt>())           = " << eve::glaisher(eve::as<wide_dt>())                << std::endl
            << "-> glaisher(as(wxd))                 = " << eve::glaisher(eve::as(wxd))                      << std::endl
            << "-> glaisher[upward](as<wide_dt>())   = " << eve::glaisher[eve::upward](eve::as<wide_dt>())   << std::endl
            << "-> glaisher[upward](as(wxd))         = " << eve::glaisher[eve::upward](eve::as(wxd))         << std::endl
            << "-> glaisher[downward](as<wide_dt>()) = " << eve::glaisher[eve::downward](eve::as<wide_dt>()) << std::endl
            << "-> glaisher[downward](as(wxd))       = " << eve::glaisher[eve::downward](eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> glaisher(as<float>())             = " << eve::glaisher(eve::as(float())) << std::endl
            << "-> glaisher(as<xf))                  = " << eve::glaisher(eve::as(xf))      << std::endl
            << "-> glaisher(as<double>())            = " << eve::glaisher(eve::as(double()))<< std::endl
            << "-> glaisher(as<xd))                  = " << eve::glaisher(eve::as(xd))      << std::endl;


  std::cout << "-> constexpr glaisher            = " << constexpr_glaisher<float>() << std::endl;

  return 0;
}
