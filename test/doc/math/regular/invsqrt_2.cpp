#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;

template<typename T>
consteval auto constexpr_invsqrt_2() { return eve::invsqrt_2(eve::as<T>{}); }

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::setprecision(9) << std::endl
            << "-> invsqrt_2(as<wide_ft>())       = " << eve::invsqrt_2(eve::as<wide_ft>())            << std::endl
            << "-> invsqrt_2(as(wxf))             = " << eve::invsqrt_2(eve::as(wxf))                  << std::endl;

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> invsqrt_2(as<float>())         = " << eve::invsqrt_2(eve::as(float())) << std::endl
            << "-> invsqrt_2(as<xf))              = " << eve::invsqrt_2(eve::as(xf))      << std::endl;


  std::cout << "-> constexpr invsqrt_2            = " << constexpr_invsqrt_2<float>() << std::endl;

  return 0;
}
