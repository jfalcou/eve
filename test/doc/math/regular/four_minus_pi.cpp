#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;
using wide_dt = eve::wide<double>;

template<typename T>
consteval auto constexpr_four_minus_pi() { return eve::four_minus_pi(eve::as<T>{}); }

int main()
{
  wide_ft wxf;
  wide_dt wxd;

  std::cout << "---- simd"  << std::setprecision(9) << std::endl
            << "-> four_minus_pi(as<wide_ft>())                 = " << eve::four_minus_pi(eve::as<wide_ft>())                << std::endl
            << "-> four_minus_pi(as(wxf))                       = " << eve::four_minus_pi(eve::as(wxf))                      << std::endl
            << "-> four_minus_pi[upward](as<wide_ft>())         = " << eve::four_minus_pi[eve::upward](eve::as<wide_ft>())   << std::endl
            << "-> four_minus_pi[upward](as(wxf))               = " << eve::four_minus_pi[eve::upward](eve::as(wxf))         << std::endl
            << "-> four_minus_pi[downward](as<wide_ft>())       = " << eve::four_minus_pi[eve::downward](eve::as<wide_ft>()) << std::endl
            << "-> four_minus_pi[downward](as(wxf))             = " << eve::four_minus_pi[eve::downward](eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> four_minus_pi(as<wide_dt>())           = " << eve::four_minus_pi(eve::as<wide_dt>())                << std::endl
            << "-> four_minus_pi(as(wxd))                 = " << eve::four_minus_pi(eve::as(wxd))                      << std::endl
            << "-> four_minus_pi[upward](as<wide_dt>())   = " << eve::four_minus_pi[eve::upward](eve::as<wide_dt>())   << std::endl
            << "-> four_minus_pi[upward](as(wxd))         = " << eve::four_minus_pi[eve::upward](eve::as(wxd))         << std::endl
            << "-> four_minus_pi[downward](as<wide_dt>()) = " << eve::four_minus_pi[eve::downward](eve::as<wide_dt>()) << std::endl
            << "-> four_minus_pi[downward](as(wxd))       = " << eve::four_minus_pi[eve::downward](eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> four_minus_pi(as<float>())             = " << eve::four_minus_pi(eve::as(float())) << std::endl
            << "-> four_minus_pi(as<xf))                  = " << eve::four_minus_pi(eve::as(xf))      << std::endl
            << "-> four_minus_pi(as<double>())            = " << eve::four_minus_pi(eve::as(double()))<< std::endl
            << "-> four_minus_pi(as<xd))                  = " << eve::four_minus_pi(eve::as(xd))      << std::endl;


  std::cout << "-> constexpr four_minus_pi            = " << constexpr_four_minus_pi<float>() << std::endl;

  return 0;
}
