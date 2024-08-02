#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float>;

template<typename T>
consteval auto constexpr_maxexponentm1() { return eve::maxexponentm1(eve::as<T>{}); }

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::endl
            << "-> maxexponentm1(as<wide_ft>())  = " << eve::maxexponentm1(eve::as<wide_ft>()) << std::endl
            << "-> maxexponentm1(as(wxf))        = " << eve::maxexponentm1(eve::as(wxf))       << std::endl;

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> maxexponentm1(as<float>())         = " << eve::maxexponentm1(eve::as(float())) << std::endl
            << "-> maxexponentm1(as<xf))              = " << eve::maxexponentm1(eve::as(xf)) << std::endl;

  std::cout << "-> constexpr maxexponentm1            = " << constexpr_maxexponentm1<float>() << std::endl;

  return 0;
}
