#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float>;

template<typename T>
consteval auto constexpr_maxexponentp1() { return eve::maxexponentp1(eve::as<T>{}); }

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::endl
            << "-> maxexponentp1(as<wide_ft>())  = " << eve::maxexponentp1(eve::as<wide_ft>()) << std::endl
            << "-> maxexponentp1(as(wxf))        = " << eve::maxexponentp1(eve::as(wxf))       << std::endl;

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> maxexponentp1(as<float>())    = " << eve::maxexponentp1(eve::as(float())) << std::endl
            << "-> maxexponentp1(as<xf))         = " << eve::maxexponentp1(eve::as(xf)) << std::endl;

  std::cout << "-> constexpr maxexponentp1            = " << constexpr_maxexponentp1<float>() << std::endl;

  return 0;
}
