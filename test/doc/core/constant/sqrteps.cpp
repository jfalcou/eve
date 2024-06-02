#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;

template<typename T>
consteval auto constexpr_sqrteps() { return eve::sqrteps(eve::as<T>{}); }

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::setprecision(9) << std::endl
            << "-> sqrteps(as<wide_ft>())              = " << eve::sqrteps(eve::as<wide_ft>()) << std::endl
            << "-> sqrteps(as(wxf))                    = " << eve::sqrteps(eve::as(wxf))       << std::endl
            << "-> sqrteps[upward](as(wxf))            = " << eve::sqrteps[eve::upward](eve::as(wxf))       << std::endl
            << "-> sqrt(double(eve::eps(as<float>()))) =  " << eve::sqrt(double(eve::eps(eve::as<float>()))) << std::endl
            << "-> sqrteps[downward](as(wxf))          = " << eve::sqrteps[eve::downward](eve::as(wxf))    << std::endl;

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> sqrteps(as<float>())         = " << eve::sqrteps(eve::as(float())) << std::endl
            << "-> sqrteps(as<xf))              = " << eve::sqrteps(eve::as(xf)) << std::endl;

  std::cout << "-> constexpr sqrteps            = " << constexpr_sqrteps<float>() << std::endl;

  return 0;
}
