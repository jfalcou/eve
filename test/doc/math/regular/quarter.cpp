#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;
using wide_dt = eve::wide<double>;

template<typename T>
consteval auto constexpr_quarter() { return eve::quarter(eve::as<T>{}); }

int main()
{
  wide_ft wxf;
  wide_dt wxd;

  std::cout << "---- simd"  << std::setprecision(9) << std::endl
            << "-> quarter(as<wide_ft>())                 = " << eve::quarter(eve::as<wide_ft>())                << std::endl
            << "-> quarter(as(wxf))                       = " << eve::quarter(eve::as(wxf))                      << std::endl
            << "-> quarter[upper](as<wide_ft>())         = " << eve::quarter[eve::upper](eve::as<wide_ft>())   << std::endl
            << "-> quarter[upper](as(wxf))               = " << eve::quarter[eve::upper](eve::as(wxf))         << std::endl
            << "-> quarter[lower](as<wide_ft>())       = " << eve::quarter[eve::lower](eve::as<wide_ft>()) << std::endl
            << "-> quarter[lower](as(wxf))             = " << eve::quarter[eve::lower](eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> quarter(as<wide_dt>())           = " << eve::quarter(eve::as<wide_dt>())                << std::endl
            << "-> quarter(as(wxd))                 = " << eve::quarter(eve::as(wxd))                      << std::endl
            << "-> quarter[upper](as<wide_dt>())   = " << eve::quarter[eve::upper](eve::as<wide_dt>())   << std::endl
            << "-> quarter[upper](as(wxd))         = " << eve::quarter[eve::upper](eve::as(wxd))         << std::endl
            << "-> quarter[lower](as<wide_dt>()) = " << eve::quarter[eve::lower](eve::as<wide_dt>()) << std::endl
            << "-> quarter[lower](as(wxd))       = " << eve::quarter[eve::lower](eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> quarter(as<float>())             = " << eve::quarter(eve::as(float())) << std::endl
            << "-> quarter(as<xf))                  = " << eve::quarter(eve::as(xf))      << std::endl
            << "-> quarter(as<double>())            = " << eve::quarter(eve::as(double()))<< std::endl
            << "-> quarter(as<xd))                  = " << eve::quarter(eve::as(xd))      << std::endl;


  std::cout << "-> constexpr quarter            = " << constexpr_quarter<float>() << std::endl;

  return 0;
}
