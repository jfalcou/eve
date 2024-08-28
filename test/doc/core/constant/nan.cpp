#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float>;

template<typename T>
consteval auto constexpr_nan() { return eve::nan(eve::as<T>{}); }

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::endl
            << "-> nan(as<wide_ft>())  = " << eve::nan(eve::as<wide_ft>()) << std::endl
            << "-> nan(as(wxf))        = " << eve::nan(eve::as(wxf))       << std::endl;

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> nan(as<float>())         = " << eve::nan(eve::as(float())) << std::endl
            << "-> nan(as<xf))              = " << eve::nan(eve::as(xf)) << std::endl;

  std::cout << "-> constexpr nan            = " << constexpr_nan<float>() << std::endl;

  return 0;
}
