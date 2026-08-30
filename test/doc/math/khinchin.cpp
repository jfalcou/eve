#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;
using wide_dt = eve::wide<double>;

template<typename T>
consteval auto constexpr_khinchin() { return eve::khinchin(eve::as<T>{}); }

int main()
{
  wide_ft wxf;
  wide_dt wxd;

  std::cout << "---- simd"  << std::setprecision(9) << std::endl
            << "-> khinchin(as<wide_ft>())                 = " << eve::khinchin(eve::as<wide_ft>())                << std::endl
            << "-> khinchin(as(wxf))                       = " << eve::khinchin(eve::as(wxf))                      << std::endl
            << "-> khinchin[upper](as<wide_ft>())         = " << eve::khinchin[eve::upper](eve::as<wide_ft>())   << std::endl
            << "-> khinchin[upper](as(wxf))               = " << eve::khinchin[eve::upper](eve::as(wxf))         << std::endl
            << "-> khinchin[lower](as<wide_ft>())       = " << eve::khinchin[eve::lower](eve::as<wide_ft>()) << std::endl
            << "-> khinchin[lower](as(wxf))             = " << eve::khinchin[eve::lower](eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> khinchin(as<wide_dt>())           = " << eve::khinchin(eve::as<wide_dt>())                << std::endl
            << "-> khinchin(as(wxd))                 = " << eve::khinchin(eve::as(wxd))                      << std::endl
            << "-> khinchin[upper](as<wide_dt>())   = " << eve::khinchin[eve::upper](eve::as<wide_dt>())   << std::endl
            << "-> khinchin[upper](as(wxd))         = " << eve::khinchin[eve::upper](eve::as(wxd))         << std::endl
            << "-> khinchin[lower](as<wide_dt>()) = " << eve::khinchin[eve::lower](eve::as<wide_dt>()) << std::endl
            << "-> khinchin[lower](as(wxd))       = " << eve::khinchin[eve::lower](eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> khinchin(as<float>())             = " << eve::khinchin(eve::as(float())) << std::endl
            << "-> khinchin(as<xf))                  = " << eve::khinchin(eve::as(xf))      << std::endl
            << "-> khinchin(as<double>())            = " << eve::khinchin(eve::as(double()))<< std::endl
            << "-> khinchin(as<xd))                  = " << eve::khinchin(eve::as(xd))      << std::endl;


  std::cout << "-> constexpr khinchin            = " << constexpr_khinchin<float>() << std::endl;

  return 0;
}
