#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;
using wide_dt = eve::wide<double>;

template<typename T>
consteval auto constexpr_pi3() { return eve::pi3(eve::as<T>{}); }

int main()
{
  wide_ft wxf;
  wide_dt wxd;

  std::cout << "---- simd"  << std::setprecision(9) << std::endl
            << "-> pi3(as<wide_ft>())                 = " << eve::pi3(eve::as<wide_ft>())                << std::endl
            << "-> pi3(as(wxf))                       = " << eve::pi3(eve::as(wxf))                      << std::endl
            << "-> pi3[upper](as<wide_ft>())         = " << eve::pi3[eve::upper](eve::as<wide_ft>())   << std::endl
            << "-> pi3[upper](as(wxf))               = " << eve::pi3[eve::upper](eve::as(wxf))         << std::endl
            << "-> pi3[lower](as<wide_ft>())       = " << eve::pi3[eve::lower](eve::as<wide_ft>()) << std::endl
            << "-> pi3[lower](as(wxf))             = " << eve::pi3[eve::lower](eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> pi3(as<wide_dt>())           = " << eve::pi3(eve::as<wide_dt>())                << std::endl
            << "-> pi3(as(wxd))                 = " << eve::pi3(eve::as(wxd))                      << std::endl
            << "-> pi3[upper](as<wide_dt>())   = " << eve::pi3[eve::upper](eve::as<wide_dt>())   << std::endl
            << "-> pi3[upper](as(wxd))         = " << eve::pi3[eve::upper](eve::as(wxd))         << std::endl
            << "-> pi3[lower](as<wide_dt>()) = " << eve::pi3[eve::lower](eve::as<wide_dt>()) << std::endl
            << "-> pi3[lower](as(wxd))       = " << eve::pi3[eve::lower](eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> pi3(as<float>())             = " << eve::pi3(eve::as(float())) << std::endl
            << "-> pi3(as<xf))                  = " << eve::pi3(eve::as(xf))      << std::endl
            << "-> pi3(as<double>())            = " << eve::pi3(eve::as(double()))<< std::endl
            << "-> pi3(as<xd))                  = " << eve::pi3(eve::as(xd))      << std::endl;


  std::cout << "-> constexpr pi3            = " << constexpr_pi3<float>() << std::endl;

  return 0;
}
