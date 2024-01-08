#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;
using wide_dt = eve::wide<double>;

int main()
{
  std::cout << "---- simd" << std::setprecision(15) << std::endl
            << "-> ieee_constant<wide_ft>(0x1.3bd3ce0p-1f, 0x1.3bd3cc9be45dep-1) " << eve::ieee_constant<wide_ft>(0x1.3bd3ce0p-1f, 0x1.3bd3cc9be45dep-1)<< std::endl
            << "-> ieee_constant<wide_dt>(0x1.3bd3ce0p-1f, 0x1.3bd3cc9be45dep-1) " << eve::ieee_constant<wide_dt>(0x1.3bd3ce0p-1f, 0x1.3bd3cc9be45dep-1)<< std::endl;

  std::cout << "---- scalar" << std::endl
            << "-> ieee_constant<float>(0x1.3bd3ce0p-1f, 0x1.3bd3cc9be45dep-1)   " << eve::ieee_constant<float>(0x1.3bd3ce0p-1f, 0x1.3bd3cc9be45dep-1)<< std::endl
            << "-> ieee_constant<double>(0x1.3bd3ce0p-1f, 0x1.3bd3cc9be45dep-1)  " << eve::ieee_constant<double>(0x1.3bd3ce0p-1f, 0x1.3bd3cc9be45dep-1)<< std::endl;

  return 0;
}
