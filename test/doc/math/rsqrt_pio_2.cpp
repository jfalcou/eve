#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;

template<typename T>
consteval auto constexpr_rsqrt_pio_2() { return eve::rsqrt_pio_2(eve::as<T>{}); }

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


  std::cout << "-> constexpr rsqrt_pio_2            = " << constexpr_rsqrt_pio_2<float>() << std::endl;

  return 0;
}
