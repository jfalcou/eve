#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;
using wide_dt = eve::wide<double>;

template<typename T>
consteval auto constexpr_pi2o_16() { return eve::pi2o_16(eve::as<T>{}); }

int main()
{
  wide_ft wxf;
  wide_dt wxd;

  std::cout << "---- simd"  << std::setprecision(9) << std::endl
            << "-> pi2o_16(as<wide_ft>())                 = " << eve::pi2o_16(eve::as<wide_ft>())                << std::endl
            << "-> pi2o_16(as(wxf))                       = " << eve::pi2o_16(eve::as(wxf))                      << std::endl
            << "-> pi2o_16[upper](as<wide_ft>())         = " << eve::pi2o_16[eve::upper](eve::as<wide_ft>())   << std::endl
            << "-> pi2o_16[upper](as(wxf))               = " << eve::pi2o_16[eve::upper](eve::as(wxf))         << std::endl
            << "-> pi2o_16[lower](as<wide_ft>())       = " << eve::pi2o_16[eve::lower](eve::as<wide_ft>()) << std::endl
            << "-> pi2o_16[lower](as(wxf))             = " << eve::pi2o_16[eve::lower](eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> pi2o_16(as<wide_dt>())           = " << eve::pi2o_16(eve::as<wide_dt>())                << std::endl
            << "-> pi2o_16(as(wxd))                 = " << eve::pi2o_16(eve::as(wxd))                      << std::endl
            << "-> pi2o_16[upper](as<wide_dt>())   = " << eve::pi2o_16[eve::upper](eve::as<wide_dt>())   << std::endl
            << "-> pi2o_16[upper](as(wxd))         = " << eve::pi2o_16[eve::upper](eve::as(wxd))         << std::endl
            << "-> pi2o_16[lower](as<wide_dt>()) = " << eve::pi2o_16[eve::lower](eve::as<wide_dt>()) << std::endl
            << "-> pi2o_16[lower](as(wxd))       = " << eve::pi2o_16[eve::lower](eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> pi2o_16(as<float>())             = " << eve::pi2o_16(eve::as(float())) << std::endl
            << "-> pi2o_16(as<xf))                  = " << eve::pi2o_16(eve::as(xf))      << std::endl
            << "-> pi2o_16(as<double>())            = " << eve::pi2o_16(eve::as(double()))<< std::endl
            << "-> pi2o_16(as<xd))                  = " << eve::pi2o_16(eve::as(xd))      << std::endl;


  std::cout << "-> constexpr pi2o_16            = " << constexpr_pi2o_16<float>() << std::endl;

  return 0;
}
