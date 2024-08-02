#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float>;

template<typename T>
consteval auto constexpr_mindenormal() { return eve::mindenormal(eve::as<T>{}); }

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::endl
            << "-> mindenormal(as<wide_ft>())  = " << eve::mindenormal(eve::as<wide_ft>()) << std::endl
            << "-> mindenormal(as(wxf))        = " << eve::mindenormal(eve::as(wxf))       << std::endl;

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> mindenormal(as<float>())         = " << eve::mindenormal(eve::as(float())) << std::endl
            << "-> mindenormal(as<xf))              = " << eve::mindenormal(eve::as(xf)) << std::endl;

  std::cout << "-> constexpr mindenormal            = " << constexpr_mindenormal<float>() << std::endl;

  return 0;
}
