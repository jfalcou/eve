#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;

template<typename T>
consteval auto constexpr_oneosqrteps() { return eve::oneosqrteps(eve::as<T>{}); }

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::setprecision(9) << std::endl
            << "-> oneosqrteps(as<wide_ft>())          = " << eve::oneosqrteps(eve::as<wide_ft>())            << std::endl
            << "-> oneosqrteps(as(wxf))                = " << eve::oneosqrteps(eve::as(wxf))                  << std::endl
            << "-> upward(oneosqrteps)(as(wxf))        = " << eve::oneosqrteps[eve::upward](eve::as(wxf))     << std::endl
            << "-> rec(eve::sqrt(double(eps((as<float>()))))) = " <<  1.0/(eve::sqrt(double(eve::eps((eve::as<float>())))))  << std::endl
            << "-> downward(oneosqrteps)(as(wxf))      = " << eve::oneosqrteps[eve::downward](eve::as(wxf))  << std::endl;

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> oneosqrteps(as<float>())         = " << eve::oneosqrteps(eve::as(float())) << std::endl
            << "-> oneosqrteps(as<xf))              = " << eve::oneosqrteps(eve::as(xf))      << std::endl;

  std::cout << "-> constexpr oneosqrteps            = " << constexpr_oneosqrteps<float>() << std::endl;

  return 0;
}
