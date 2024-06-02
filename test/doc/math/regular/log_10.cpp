#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;

template<typename T>
consteval auto constexpr_log_10() { return eve::log_10(eve::as<T>{}); }

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::setprecision(9) << std::endl
            << "-> log_10(as<wide_ft>())       = " << eve::log_10(eve::as<wide_ft>())            << std::endl
            << "-> log_10(as(wxf))             = " << eve::log_10(eve::as(wxf))                  << std::endl;

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> log_10(as<float>())         = " << eve::log_10(eve::as(float())) << std::endl
            << "-> log_10(as<xf))              = " << eve::log_10(eve::as(xf))      << std::endl;


  std::cout << "-> constexpr log_10            = " << constexpr_log_10<float>() << std::endl;

  return 0;
}
