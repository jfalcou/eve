#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;

template<typename T>
consteval auto constexpr_euler() { return eve::euler(eve::as<T>{}); }

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::setprecision(9) << std::endl
            << "-> euler(as<wide_ft>())        = " << eve::euler(eve::as<wide_ft>())            << std::endl
            << "-> euler(as(wxf))              = " << eve::euler(eve::as(wxf))                  << std::endl;

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> euler(as<float>())         = " << eve::euler(eve::as(float())) << std::endl
            << "-> euler(as<xf))              = " << eve::euler(eve::as(xf))      << std::endl;


  std::cout << "-> constexpr euler            = " << constexpr_euler<float>() << std::endl;

  return 0;
}
