#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;
using wide_dt = eve::wide<double>;

template<typename T>
consteval auto constexpr_two_o_sqrt_pi() { return eve::two_o_sqrt_pi(eve::as<T>{}); }

int main()
{
  wide_ft wxf;
  wide_dt wxd;

  std::cout << "---- simd"  << std::setprecision(9) << std::endl
            << "-> two_o_sqrt_pi(as<wide_ft>())                 = " << eve::two_o_sqrt_pi(eve::as<wide_ft>())                << std::endl
            << "-> two_o_sqrt_pi(as(wxf))                       = " << eve::two_o_sqrt_pi(eve::as(wxf))                      << std::endl
            << "-> two_o_sqrt_pi[upward](as<wide_ft>())         = " << eve::two_o_sqrt_pi[eve::upward](eve::as<wide_ft>())   << std::endl
            << "-> two_o_sqrt_pi[upward](as(wxf))               = " << eve::two_o_sqrt_pi[eve::upward](eve::as(wxf))         << std::endl
            << "-> two_o_sqrt_pi[downward](as<wide_ft>())       = " << eve::two_o_sqrt_pi[eve::downward](eve::as<wide_ft>()) << std::endl
            << "-> two_o_sqrt_pi[downward](as(wxf))             = " << eve::two_o_sqrt_pi[eve::downward](eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> two_o_sqrt_pi(as<wide_dt>())           = " << eve::two_o_sqrt_pi(eve::as<wide_dt>())                << std::endl
            << "-> two_o_sqrt_pi(as(wxd))                 = " << eve::two_o_sqrt_pi(eve::as(wxd))                      << std::endl
            << "-> two_o_sqrt_pi[upward](as<wide_dt>())   = " << eve::two_o_sqrt_pi[eve::upward](eve::as<wide_dt>())   << std::endl
            << "-> two_o_sqrt_pi[upward](as(wxd))         = " << eve::two_o_sqrt_pi[eve::upward](eve::as(wxd))         << std::endl
            << "-> two_o_sqrt_pi[downward](as<wide_dt>()) = " << eve::two_o_sqrt_pi[eve::downward](eve::as<wide_dt>()) << std::endl
            << "-> two_o_sqrt_pi[downward](as(wxd))       = " << eve::two_o_sqrt_pi[eve::downward](eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> two_o_sqrt_pi(as<float>())             = " << eve::two_o_sqrt_pi(eve::as(float())) << std::endl
            << "-> two_o_sqrt_pi(as<xf))                  = " << eve::two_o_sqrt_pi(eve::as(xf))      << std::endl
            << "-> two_o_sqrt_pi(as<double>())            = " << eve::two_o_sqrt_pi(eve::as(double()))<< std::endl
            << "-> two_o_sqrt_pi(as<xd))                  = " << eve::two_o_sqrt_pi(eve::as(xd))      << std::endl;


  std::cout << "-> constexpr two_o_sqrt_pi            = " << constexpr_two_o_sqrt_pi<float>() << std::endl;

  return 0;
}
