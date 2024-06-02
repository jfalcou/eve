#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;

template<typename T>
consteval auto constexpr_inv_pi() { return eve::inv_pi(eve::as<T>{}); }

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::setprecision(9) << std::endl
            << "-> inv_pi(as<wide_ft>())       = " << eve::inv_pi(eve::as<wide_ft>())            << std::endl
            << "-> inv_pi(as(wxf))             = " << eve::inv_pi(eve::as(wxf))                  << std::endl;

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> inv_pi(as<float>())         = " << eve::inv_pi(eve::as(float())) << std::endl
            << "-> inv_pi(as<xf))              = " << eve::inv_pi(eve::as(xf))      << std::endl;


  std::cout << "-> constexpr inv_pi            = " << constexpr_inv_pi<float>() << std::endl;

  return 0;
}
