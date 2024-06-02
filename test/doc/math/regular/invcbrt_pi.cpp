#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;
using wide_dt = eve::wide<double>;

template<typename T>
consteval auto constexpr_invcbrt_pi() { return eve::invcbrt_pi(eve::as<T>{}); }

int main()
{
  wide_ft wxf;
  wide_dt wxd;

  std::cout << "---- simd"  << std::setprecision(9) << std::endl
            << "-> invcbrt_pi(as<wide_ft>())                 = " << eve::invcbrt_pi(eve::as<wide_ft>())                << std::endl
            << "-> invcbrt_pi(as(wxf))                       = " << eve::invcbrt_pi(eve::as(wxf))                      << std::endl
            << "-> invcbrt_pi[upward](as<wide_ft>())         = " << eve::invcbrt_pi[eve::upward](eve::as<wide_ft>())   << std::endl
            << "-> invcbrt_pi[upward](as(wxf))               = " << eve::invcbrt_pi[eve::upward](eve::as(wxf))         << std::endl
            << "-> invcbrt_pi[downward](as<wide_ft>())       = " << eve::invcbrt_pi[eve::downward](eve::as<wide_ft>()) << std::endl
            << "-> invcbrt_pi[downward](as(wxf))             = " << eve::invcbrt_pi[eve::downward](eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> invcbrt_pi(as<wide_dt>())           = " << eve::invcbrt_pi(eve::as<wide_dt>())                << std::endl
            << "-> invcbrt_pi(as(wxd))                 = " << eve::invcbrt_pi(eve::as(wxd))                      << std::endl
            << "-> invcbrt_pi[upward](as<wide_dt>())   = " << eve::invcbrt_pi[eve::upward](eve::as<wide_dt>())   << std::endl
            << "-> invcbrt_pi[upward](as(wxd))         = " << eve::invcbrt_pi[eve::upward](eve::as(wxd))         << std::endl
            << "-> invcbrt_pi[downward](as<wide_dt>()) = " << eve::invcbrt_pi[eve::downward](eve::as<wide_dt>()) << std::endl
            << "-> invcbrt_pi[downward](as(wxd))       = " << eve::invcbrt_pi[eve::downward](eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> invcbrt_pi(as<float>())             = " << eve::invcbrt_pi(eve::as(float())) << std::endl
            << "-> invcbrt_pi(as<xf))                  = " << eve::invcbrt_pi(eve::as(xf))      << std::endl
            << "-> invcbrt_pi(as<double>())            = " << eve::invcbrt_pi(eve::as(double()))<< std::endl
            << "-> invcbrt_pi(as<xd))                  = " << eve::invcbrt_pi(eve::as(xd))      << std::endl;


  std::cout << "-> constexpr invcbrt_pi            = " << constexpr_invcbrt_pi<float>() << std::endl;

  return 0;
}
