#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;

template<typename T>
consteval auto constexpr_pio_4() { return eve::pio_4(eve::as<T>{}); }

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::setprecision(9) << std::endl
            << "-> pio_4(as<wide_ft>())        = " << eve::pio_4(eve::as<wide_ft>())            << std::endl
            << "-> pio_4(as(wxf))              = " << eve::pio_4(eve::as(wxf))                  << std::endl;

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> pio_4(as<float>())         = " << eve::pio_4(eve::as(float())) << std::endl
            << "-> pio_4(as<xf))              = " << eve::pio_4(eve::as(xf))      << std::endl;


  std::cout << "-> constexpr pio_4            = " << constexpr_pio_4<float>() << std::endl;

  return 0;
}
