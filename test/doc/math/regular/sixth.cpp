#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;
using wide_dt = eve::wide<double>;

template<typename T>
consteval auto constexpr_sixth() { return eve::sixth(eve::as<T>{}); }

int main()
{
  wide_ft wxf;
  wide_dt wxd;

  std::cout << "---- simd"  << std::setprecision(9) << std::endl
            << "-> sixth(as<wide_ft>())                 = " << eve::sixth(eve::as<wide_ft>())                << std::endl
            << "-> sixth(as(wxf))                       = " << eve::sixth(eve::as(wxf))                      << std::endl
            << "-> sixth[upward](as<wide_ft>())         = " << eve::sixth[eve::upward](eve::as<wide_ft>())   << std::endl
            << "-> sixth[upward](as(wxf))               = " << eve::sixth[eve::upward](eve::as(wxf))         << std::endl
            << "-> sixth[downward](as<wide_ft>())       = " << eve::sixth[eve::downward](eve::as<wide_ft>()) << std::endl
            << "-> sixth[downward](as(wxf))             = " << eve::sixth[eve::downward](eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> sixth(as<wide_dt>())           = " << eve::sixth(eve::as<wide_dt>())                << std::endl
            << "-> sixth(as(wxd))                 = " << eve::sixth(eve::as(wxd))                      << std::endl
            << "-> sixth[upward](as<wide_dt>())   = " << eve::sixth[eve::upward](eve::as<wide_dt>())   << std::endl
            << "-> sixth[upward](as(wxd))         = " << eve::sixth[eve::upward](eve::as(wxd))         << std::endl
            << "-> sixth[downward](as<wide_dt>()) = " << eve::sixth[eve::downward](eve::as<wide_dt>()) << std::endl
            << "-> sixth[downward](as(wxd))       = " << eve::sixth[eve::downward](eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> sixth(as<float>())             = " << eve::sixth(eve::as(float())) << std::endl
            << "-> sixth(as<xf))                  = " << eve::sixth(eve::as(xf))      << std::endl
            << "-> sixth(as<double>())            = " << eve::sixth(eve::as(double()))<< std::endl
            << "-> sixth(as<xd))                  = " << eve::sixth(eve::as(xd))      << std::endl;


  std::cout << "-> constexpr sixth            = " << constexpr_sixth<float>() << std::endl;

  return 0;
}
