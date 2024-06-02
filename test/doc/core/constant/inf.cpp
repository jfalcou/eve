#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float>;

template<typename T>
consteval auto constexpr_inf() { return eve::inf(eve::as<T>{}); }

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::endl
            << "-> inf(as<wide_ft>())  = " << eve::inf(eve::as<wide_ft>()) << std::endl
            << "-> inf(as(wxf))        = " << eve::inf(eve::as(wxf))       << std::endl;

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> inf(as<float>())         = " << eve::inf(eve::as(float())) << std::endl
            << "-> inf(as<xf))              = " << eve::inf(eve::as(xf)) << std::endl;

  std::cout << "-> constexpr inf            = " << constexpr_inf<float>() << std::endl;

  return 0;
}
