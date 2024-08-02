#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float>;

template<typename T>
consteval auto constexpr_exponentmask() { return eve::exponentmask(eve::as<T>{}); }

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::endl
            << "-> exponentmask(as<wide_ft>())  = " << eve::exponentmask(eve::as<wide_ft>()) << std::endl
            << "-> exponentmask(as(wxf))        = " << eve::exponentmask(eve::as(wxf))       << std::endl;

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> exponentmask(as<float>())         = " << eve::exponentmask(eve::as(float())) << std::endl
            << "-> exponentmask(as<xf))              = " << eve::exponentmask(eve::as(xf)) << std::endl;

  std::cout << "-> constexpr exponentmask            = " << constexpr_exponentmask<float>() << std::endl;

  return 0;
}
