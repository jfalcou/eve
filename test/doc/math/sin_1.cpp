#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;
using wide_dt = eve::wide<double>;

template<typename T>
consteval auto constexpr_sin_1() { return eve::sin_1(eve::as<T>{}); }

int main()
{
  wide_ft wxf;
  wide_dt wxd;

  std::cout << "---- simd"  << std::setprecision(9) << std::endl
            << "-> sin_1(as<wide_ft>())                 = " << eve::sin_1(eve::as<wide_ft>())                << std::endl
            << "-> sin_1(as(wxf))                       = " << eve::sin_1(eve::as(wxf))                      << std::endl
            << "-> sin_1[upper](as<wide_ft>())         = " << eve::sin_1[eve::upper](eve::as<wide_ft>())   << std::endl
            << "-> sin_1[upper](as(wxf))               = " << eve::sin_1[eve::upper](eve::as(wxf))         << std::endl
            << "-> sin_1[lower](as<wide_ft>())       = " << eve::sin_1[eve::lower](eve::as<wide_ft>()) << std::endl
            << "-> sin_1[lower](as(wxf))             = " << eve::sin_1[eve::lower](eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> sin_1(as<wide_dt>())           = " << eve::sin_1(eve::as<wide_dt>())                << std::endl
            << "-> sin_1(as(wxd))                 = " << eve::sin_1(eve::as(wxd))                      << std::endl
            << "-> sin_1[upper](as<wide_dt>())   = " << eve::sin_1[eve::upper](eve::as<wide_dt>())   << std::endl
            << "-> sin_1[upper](as(wxd))         = " << eve::sin_1[eve::upper](eve::as(wxd))         << std::endl
            << "-> sin_1[lower](as<wide_dt>()) = " << eve::sin_1[eve::lower](eve::as<wide_dt>()) << std::endl
            << "-> sin_1[lower](as(wxd))       = " << eve::sin_1[eve::lower](eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> sin_1(as<float>())             = " << eve::sin_1(eve::as(float())) << std::endl
            << "-> sin_1(as<xf))                  = " << eve::sin_1(eve::as(xf))      << std::endl
            << "-> sin_1(as<double>())            = " << eve::sin_1(eve::as(double()))<< std::endl
            << "-> sin_1(as<xd))                  = " << eve::sin_1(eve::as(xd))      << std::endl;


  std::cout << "-> constexpr sin_1            = " << constexpr_sin_1<float>() << std::endl;

  return 0;
}
