#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;

template<typename T>
consteval auto constexpr_invlog_2() { return eve::invlog_2(eve::as<T>{}); }

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::setprecision(9) << std::endl
            << "-> invlog_2(as<wide_ft>())       = " << eve::invlog_2(eve::as<wide_ft>())            << std::endl
            << "-> invlog_2(as(wxf))             = " << eve::invlog_2(eve::as(wxf))                  << std::endl;

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> invlog_2(as<float>())         = " << eve::invlog_2(eve::as(float())) << std::endl
            << "-> invlog_2(as<xf))              = " << eve::invlog_2(eve::as(xf))      << std::endl;


  std::cout << "-> constexpr invlog_2            = " << constexpr_invlog_2<float>() << std::endl;

  return 0;
}
