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
            << "-> quarter[upward](as<wide_ft>())         = " << eve::quarter[eve::upward](eve::as<wide_ft>())   << std::endl
            << "-> quarter[upward](as(wxf))               = " << eve::quarter[eve::upward](eve::as(wxf))         << std::endl
            << "-> quarter[downward](as<wide_ft>())       = " << eve::quarter[eve::downward](eve::as<wide_ft>()) << std::endl
            << "-> quarter[downward](as(wxf))             = " << eve::quarter[eve::downward](eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> quarter(as<wide_dt>())           = " << eve::quarter(eve::as<wide_dt>())                << std::endl
            << "-> quarter(as(wxd))                 = " << eve::quarter(eve::as(wxd))                      << std::endl
            << "-> quarter[upward](as<wide_dt>())   = " << eve::quarter[eve::upward](eve::as<wide_dt>())   << std::endl
            << "-> quarter[upward](as(wxd))         = " << eve::quarter[eve::upward](eve::as(wxd))         << std::endl
            << "-> quarter[downward](as<wide_dt>()) = " << eve::quarter[eve::downward](eve::as<wide_dt>()) << std::endl
            << "-> quarter[downward](as(wxd))       = " << eve::quarter[eve::downward](eve::as(wxd))       << std::endl;

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
