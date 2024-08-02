#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float>;

template<typename T>
consteval auto constexpr_mantissamask() { return eve::mantissamask(eve::as<T>{}); }

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::endl
            << "-> mantissamask(as<wide_ft>())  = " << eve::mantissamask(eve::as<wide_ft>()) << std::endl
            << "-> mantissamask(as(wxf))        = " << eve::mantissamask(eve::as(wxf))       << std::endl;

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> mantissamask(as<float>())         = " << eve::mantissamask(eve::as(float())) << std::endl
            << "-> mantissamask(as<xf))              = " << eve::mantissamask(eve::as(xf)) << std::endl;

  std::cout << "-> constexpr mantissamask            = " << constexpr_mantissamask<float>() << std::endl;

  return 0;
}
