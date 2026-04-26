#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;

template<typename T>
consteval auto constexpr_max_safe_integer() { return eve::max_safe_integer(eve::as<T>{}); }

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::endl
            << "-> max_safe_integer(as<wide_ft>())       = " << eve::max_safe_integer(eve::as<wide_ft>()) << std::endl
            << "-> max_safe_integer(as(wxf))             = " << eve::max_safe_integer(eve::as(wxf))       << std::endl;

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> max_safe_integer(as<float>())         = " << std::setprecision(17) << eve::max_safe_integer(eve::as(float())) << std::endl
            << "-> max_safe_integer(as<xf))              = " << std::setprecision(17) << eve::max_safe_integer(eve::as(xf)) << std::endl;

  std::cout << "-> constexpr max_safe_integer            = " << constexpr_max_safe_integer<float>() << std::endl;

  return 0;
}
