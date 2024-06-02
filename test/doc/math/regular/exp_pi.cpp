#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;
using wide_dt = eve::wide<double>;

template<typename T>
consteval auto constexpr_exp_pi() { return eve::exp_pi(eve::as<T>{}); }

int main()
{
  wide_ft wxf;
  wide_dt wxd;

  std::cout << "---- simd"  << std::setprecision(9) << std::endl
            << "-> exp_pi(as<wide_ft>())                 = " << eve::exp_pi(eve::as<wide_ft>())                << std::endl
            << "-> exp_pi(as(wxf))                       = " << eve::exp_pi(eve::as(wxf))                      << std::endl
            << "-> exp_pi[upward](as<wide_ft>())         = " << eve::exp_pi[eve::upward](eve::as<wide_ft>())   << std::endl
            << "-> exp_pi[upward](as(wxf))               = " << eve::exp_pi[eve::upward](eve::as(wxf))         << std::endl
            << "-> exp_pi[downward](as<wide_ft>())       = " << eve::exp_pi[eve::downward](eve::as<wide_ft>()) << std::endl
            << "-> exp_pi[downward](as(wxf))             = " << eve::exp_pi[eve::downward](eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> exp_pi(as<wide_dt>())           = " << eve::exp_pi(eve::as<wide_dt>())                << std::endl
            << "-> exp_pi(as(wxd))                 = " << eve::exp_pi(eve::as(wxd))                      << std::endl
            << "-> exp_pi[upward](as<wide_dt>())   = " << eve::exp_pi[eve::upward](eve::as<wide_dt>())   << std::endl
            << "-> exp_pi[upward](as(wxd))         = " << eve::exp_pi[eve::upward](eve::as(wxd))         << std::endl
            << "-> exp_pi[downward](as<wide_dt>()) = " << eve::exp_pi[eve::downward](eve::as<wide_dt>()) << std::endl
            << "-> exp_pi[downward](as(wxd))       = " << eve::exp_pi[eve::downward](eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> exp_pi(as<float>())             = " << eve::exp_pi(eve::as(float())) << std::endl
            << "-> exp_pi(as<xf))                  = " << eve::exp_pi(eve::as(xf))      << std::endl
            << "-> exp_pi(as<double>())            = " << eve::exp_pi(eve::as(double()))<< std::endl
            << "-> exp_pi(as<xd))                  = " << eve::exp_pi(eve::as(xd))      << std::endl;


  std::cout << "-> constexpr exp_pi            = " << constexpr_exp_pi<float>() << std::endl;

  return 0;
}
