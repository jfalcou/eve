#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::setprecision(9) << std::endl
            << "-> rsqrt_pio_2(as<wide_ft>())       = " << eve::rsqrt_pio_2(eve::as<wide_ft>())            << std::endl
            << "-> rsqrt_pio_2(as(wxf))             = " << eve::rsqrt_pio_2(eve::as(wxf))                  << std::endl;

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> rsqrt_pio_2(as<float>())         = " << eve::rsqrt_pio_2(eve::as(float())) << std::endl
            << "-> rsqrt_pio_2(as<xf))              = " << eve::rsqrt_pio_2(eve::as(xf))      << std::endl;

  return 0;
}
