#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;

template<typename T>
consteval auto constexpr_minlog10denormal() { return eve::minlog10denormal(eve::as<T>{}); }

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::setprecision(9) << std::endl
            << "-> minlog10denormal(as<wide_ft>())        = " << eve::minlog10denormal(eve::as<wide_ft>())            << std::endl
            << "-> minlog10denormal(as(wxf))              = " << eve::minlog10denormal(eve::as(wxf))                  << std::endl;

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> minlog10denormal(as<float>())         = " << eve::minlog10denormal(eve::as(float())) << std::endl
            << "-> minlog10denormal(as<xf))              = " << eve::minlog10denormal(eve::as(xf))      << std::endl;


  std::cout << "-> constexpr minlog10denormal            = " << constexpr_minlog10denormal<float>() << std::endl;

  return 0;
}
