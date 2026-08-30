#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;

template<typename T>
consteval auto constexpr_maxlog10() { return eve::maxlog10(eve::as<T>{}); }

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::setprecision(9) << std::endl
            << "-> maxlog10(as<wide_ft>())        = " << eve::maxlog10(eve::as<wide_ft>())            << std::endl
            << "-> maxlog10(as(wxf))              = " << eve::maxlog10(eve::as(wxf))                  << std::endl;

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> maxlog10(as<float>())         = " << eve::maxlog10(eve::as(float())) << std::endl
            << "-> maxlog10(as<xf))              = " << eve::maxlog10(eve::as(xf))      << std::endl;


  std::cout << "-> constexpr maxlog10            = " << constexpr_maxlog10<float>() << std::endl;

  return 0;
}
