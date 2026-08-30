#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;
using wide_dt = eve::wide<double>;

template<typename T>
consteval auto constexpr_egamma_sqr() { return eve::egamma_sqr(eve::as<T>{}); }

int main()
{
  wide_ft wxf;
  wide_dt wxd;

  std::cout << "---- simd"  << std::setprecision(9) << std::endl
            << "-> egamma_sqr(as<wide_ft>())                 = " << eve::egamma_sqr(eve::as<wide_ft>())                << std::endl
            << "-> egamma_sqr(as(wxf))                       = " << eve::egamma_sqr(eve::as(wxf))                      << std::endl
            << "-> egamma_sqr[upper](as<wide_ft>())         = " << eve::egamma_sqr[eve::upper](eve::as<wide_ft>())   << std::endl
            << "-> egamma_sqr[upper](as(wxf))               = " << eve::egamma_sqr[eve::upper](eve::as(wxf))         << std::endl
            << "-> egamma_sqr[lower](as<wide_ft>())       = " << eve::egamma_sqr[eve::lower](eve::as<wide_ft>()) << std::endl
            << "-> egamma_sqr[lower](as(wxf))             = " << eve::egamma_sqr[eve::lower](eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> egamma_sqr(as<wide_dt>())           = " << eve::egamma_sqr(eve::as<wide_dt>())                << std::endl
            << "-> egamma_sqr(as(wxd))                 = " << eve::egamma_sqr(eve::as(wxd))                      << std::endl
            << "-> egamma_sqr[upper](as<wide_dt>())   = " << eve::egamma_sqr[eve::upper](eve::as<wide_dt>())   << std::endl
            << "-> egamma_sqr[upper](as(wxd))         = " << eve::egamma_sqr[eve::upper](eve::as(wxd))         << std::endl
            << "-> egamma_sqr[lower](as<wide_dt>()) = " << eve::egamma_sqr[eve::lower](eve::as<wide_dt>()) << std::endl
            << "-> egamma_sqr[lower](as(wxd))       = " << eve::egamma_sqr[eve::lower](eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> egamma_sqr(as<float>())             = " << eve::egamma_sqr(eve::as(float())) << std::endl
            << "-> egamma_sqr(as<xf))                  = " << eve::egamma_sqr(eve::as(xf))      << std::endl
            << "-> egamma_sqr(as<double>())            = " << eve::egamma_sqr(eve::as(double()))<< std::endl
            << "-> egamma_sqr(as<xd))                  = " << eve::egamma_sqr(eve::as(xd))      << std::endl;


  std::cout << "-> constexpr egamma_sqr            = " << constexpr_egamma_sqr<float>() << std::endl;

  return 0;
}
