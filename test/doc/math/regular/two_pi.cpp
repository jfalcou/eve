#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;

template<typename T>
consteval auto constexpr_two_pi() { return eve::two_pi(eve::as<T>{}); }

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::setprecision(9) << std::endl
            << "-> two_pi(as<wide_ft>())       = " << eve::two_pi(eve::as<wide_ft>())            << std::endl
            << "-> two_pi(as(wxf))             = " << eve::two_pi(eve::as(wxf))                  << std::endl;

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> two_pi(as<float>())         = " << eve::two_pi(eve::as(float())) << std::endl
            << "-> two_pi(as<xf))              = " << eve::two_pi(eve::as(xf))      << std::endl;


  std::cout << "-> constexpr two_pi            = " << constexpr_two_pi<float>() << std::endl;

  return 0;
}
