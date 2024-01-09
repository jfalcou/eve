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
            << "-> ieee_cts<0x1.3bd3ce0p-1f, 0x1.3bd3cc9be45dep-1(targetwf) " << eve::ieee_cts<0x1.3bd3ce0p-1f, 0x1.3bd3cc9be45dep-1>(targetwf)<< std::endl
            << "-> ieee_cts<0x1.3bd3ce0p-1f, 0x1.3bd3cc9be45dep-1>(targetwd) " << eve::ieee_cts<0x1.3bd3ce0p-1f, 0x1.3bd3cc9be45dep-1>(targetwd)<< std::endl;

  auto targetf = eve::as<float>{};
  auto targetd = eve::as<double>{};
  std::cout << "---- scalar" << std::endl
            << "-> ieee_cts<0x1.3bd3ce0p-1f, 0x1.3bd3cc9be45dep-1>(targetf)   " << eve::ieee_cts<0x1.3bd3ce0p-1f, 0x1.3bd3cc9be45dep-1>(targetf)<< std::endl
            << "-> ieee_cts<0x1.3bd3ce0p-1f, 0x1.3bd3cc9be45dep-1>(targetd)  " << eve::ieee_cts<0x1.3bd3ce0p-1f, 0x1.3bd3cc9be45dep-1>(targetd) << std::endl;

  return 0;
}
