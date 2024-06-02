#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;
using wide_dt = eve::wide<double>;

template<typename T>
consteval auto constexpr_third() { return eve::third(eve::as<T>{}); }

int main()
{
  wide_ft wxf;
  wide_dt wxd;

  std::cout << "---- simd"  << std::setprecision(9) << std::endl
            << "-> third(as<wide_ft>())                 = " << eve::third(eve::as<wide_ft>())                << std::endl
            << "-> third(as(wxf))                       = " << eve::third(eve::as(wxf))                      << std::endl
            << "-> third[upward](as<wide_ft>())         = " << eve::third[eve::upward](eve::as<wide_ft>())   << std::endl
            << "-> third[upward](as(wxf))               = " << eve::third[eve::upward](eve::as(wxf))         << std::endl
            << "-> third[downward](as<wide_ft>())       = " << eve::third[eve::downward](eve::as<wide_ft>()) << std::endl
            << "-> third[downward](as(wxf))             = " << eve::third[eve::downward](eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> third(as<wide_dt>())           = " << eve::third(eve::as<wide_dt>())                << std::endl
            << "-> third(as(wxd))                 = " << eve::third(eve::as(wxd))                      << std::endl
            << "-> third[upward](as<wide_dt>())   = " << eve::third[eve::upward](eve::as<wide_dt>())   << std::endl
            << "-> third[upward](as(wxd))         = " << eve::third[eve::upward](eve::as(wxd))         << std::endl
            << "-> third[downward](as<wide_dt>()) = " << eve::third[eve::downward](eve::as<wide_dt>()) << std::endl
            << "-> third[downward](as(wxd))       = " << eve::third[eve::downward](eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> third(as<float>())             = " << eve::third(eve::as(float())) << std::endl
            << "-> third(as<xf))                  = " << eve::third(eve::as(xf))      << std::endl
            << "-> third(as<double>())            = " << eve::third(eve::as(double()))<< std::endl
            << "-> third(as<xd))                  = " << eve::third(eve::as(xd))      << std::endl;


  std::cout << "-> constexpr third            = " << constexpr_third<float>() << std::endl;

  return 0;
}
