#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float>;

template<typename T>
consteval auto constexpr_minexponent() { return eve::minexponent(eve::as<T>{}); }

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::endl
            << "-> minexponent(as<wide_ft>())  = " << eve::minexponent(eve::as<wide_ft>()) << std::endl
            << "-> minexponent(as(wxf))        = " << eve::minexponent(eve::as(wxf))       << std::endl;

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> minexponent(as<float>())         = " << eve::minexponent(eve::as(float())) << std::endl
            << "-> minexponent(as<xf))              = " << eve::minexponent(eve::as(xf)) << std::endl;

  std::cout << "-> constexpr minexponent            = " << constexpr_minexponent<float>() << std::endl;

  return 0;
}
