#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float>;

template<typename T>
consteval auto constexpr_half() { return eve::half(eve::as<T>{}); }

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::endl
            << "-> half(as<wide_ft>())  = " << eve::half(eve::as<wide_ft>()) << std::endl
            << "-> half(as(wxf))        = " << eve::half(eve::as(wxf))       << std::endl;

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> half(as<float>())         = " << eve::half(eve::as(float())) << std::endl
            << "-> half(as<xf))              = " << eve::half(eve::as(xf)) << std::endl;

  std::cout << "-> constexpr half            = " << constexpr_half<float>() << std::endl;

  return 0;
}
