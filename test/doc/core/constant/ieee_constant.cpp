#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;
using wide_dt = eve::wide<double>;

int main()
{
  auto targetwf = eve::as<wide_ft>{};
  auto targetwd = eve::as<wide_dt>{};
  std::cout << "---- simd" << std::setprecision(15) << std::endl
            << "-> ieee_constant<0x1.3bd3cc9be45dep-1, 0x1.3bd3ce0p-1f)(targetwf) " << eve::ieee_constant<0x1.3bd3cc9be45dep-1, 0x1.3bd3ce0p-1f>(targetwf)<< std::endl
            << "-> ieee_constant<0x1.3bd3cc9be45dep-1, 0x1.3bd3ce0p-1f>(targetwd) " << eve::ieee_constant<0x1.3bd3cc9be45dep-1, 0x1.3bd3ce0p-1f>(targetwd)<< std::endl;

  auto targetf = eve::as<float>{};
  auto targetd = eve::as<double>{};
  std::cout << "---- scalar" << std::endl
            << "-> ieee_constant<0x1.3bd3cc9be45dep-1, 0x1.3bd3ce0p-1f)(targetf) " << eve::ieee_constant<0x1.3bd3cc9be45dep-1, 0x1.3bd3ce0p-1f>(targetf)<< std::endl
            << "-> ieee_constant<0x1.3bd3cc9be45dep-1, 0x1.3bd3ce0p-1f>(targetd) " << eve::ieee_constant<0x1.3bd3cc9be45dep-1, 0x1.3bd3ce0p-1f>(targetd)<< std::endl;

  return 0;
}
