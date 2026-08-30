#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;

template<typename T>
consteval auto constexpr_minlogdenormal() { return eve::minlogdenormal(eve::as<T>{}); }

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::setprecision(9) << std::endl
            << "-> minlogdenormal(as<wide_ft>())        = " << eve::minlogdenormal(eve::as<wide_ft>())            << std::endl
            << "-> minlogdenormal(as(wxf))              = " << eve::minlogdenormal(eve::as(wxf))                  << std::endl;

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> minlogdenormal(as<float>())         = " << eve::minlogdenormal(eve::as(float())) << std::endl
            << "-> minlogdenormal(as<xf))              = " << eve::minlogdenormal(eve::as(xf))      << std::endl;


  std::cout << "-> constexpr minlogdenormal            = " << constexpr_minlogdenormal<float>() << std::endl;

  return 0;
}
