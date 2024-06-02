#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;
using wide_dt = eve::wide<double>;

template<typename T>
consteval auto constexpr_rsqrt_2pi() { return eve::rsqrt_2pi(eve::as<T>{}); }

int main()
{
  wide_ft wxf;
  wide_dt wxd;

  std::cout << "---- simd"  << std::setprecision(9) << std::endl
            << "-> rsqrt_2pi(as<wide_ft>())                 = " << eve::rsqrt_2pi(eve::as<wide_ft>())                << std::endl
            << "-> rsqrt_2pi(as(wxf))                       = " << eve::rsqrt_2pi(eve::as(wxf))                      << std::endl
            << "-> rsqrt_2pi[upward](as<wide_ft>())         = " << eve::rsqrt_2pi[eve::upward](eve::as<wide_ft>())   << std::endl
            << "-> rsqrt_2pi[upward](as(wxf))               = " << eve::rsqrt_2pi[eve::upward](eve::as(wxf))         << std::endl
            << "-> rsqrt_2pi[downward](as<wide_ft>())       = " << eve::rsqrt_2pi[eve::downward](eve::as<wide_ft>()) << std::endl
            << "-> rsqrt_2pi[downward](as(wxf))             = " << eve::rsqrt_2pi[eve::downward](eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> rsqrt_2pi(as<wide_dt>())           = " << eve::rsqrt_2pi(eve::as<wide_dt>())                << std::endl
            << "-> rsqrt_2pi(as(wxd))                 = " << eve::rsqrt_2pi(eve::as(wxd))                      << std::endl
            << "-> rsqrt_2pi[upward](as<wide_dt>())   = " << eve::rsqrt_2pi[eve::upward](eve::as<wide_dt>())   << std::endl
            << "-> rsqrt_2pi[upward](as(wxd))         = " << eve::rsqrt_2pi[eve::upward](eve::as(wxd))         << std::endl
            << "-> rsqrt_2pi[downward](as<wide_dt>()) = " << eve::rsqrt_2pi[eve::downward](eve::as<wide_dt>()) << std::endl
            << "-> rsqrt_2pi[downward](as(wxd))       = " << eve::rsqrt_2pi[eve::downward](eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> rsqrt_2pi(as<float>())             = " << eve::rsqrt_2pi(eve::as(float())) << std::endl
            << "-> rsqrt_2pi(as<xf))                  = " << eve::rsqrt_2pi(eve::as(xf))      << std::endl
            << "-> rsqrt_2pi(as<double>())            = " << eve::rsqrt_2pi(eve::as(double()))<< std::endl
            << "-> rsqrt_2pi(as<xd))                  = " << eve::rsqrt_2pi(eve::as(xd))      << std::endl;


  std::cout << "-> constexpr rsqrt_2pi            = " << constexpr_rsqrt_2pi<float>() << std::endl;

  return 0;
}
