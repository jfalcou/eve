#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;

template<typename T>
consteval auto constexpr_inv_egamma() { return eve::inv_egamma(eve::as<T>{}); }

int main()
{

  std::cout << "---- simd"  << std::setprecision(9) << std::endl
            << "-> inv_egamma(as<wide_ft>())                 = " << eve::inv_egamma(eve::as<wide_ft>())                << std::endl
            << "-> inv_egamma[upward](as<wide_ft>())         = " << eve::inv_egamma[eve::upward](eve::as<wide_ft>())   << std::endl
            << "-> inv_egamma[downward](as<wide_ft>())       = " << eve::inv_egamma[eve::downward](eve::as<wide_ft>()) << std::endl;


  std::cout << "---- scalar" << std::endl
            << "-> inv_egamma(as<float>())             = " << eve::inv_egamma(eve::as(float())) << std::endl;


  std::cout << "-> constexpr inv_egamma            = " << constexpr_inv_egamma<float>() << std::endl;

  return 0;
}
