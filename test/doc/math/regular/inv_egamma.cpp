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
            << "-> inv_egamma[upper](as<wide_ft>())         = " << eve::inv_egamma[eve::upper](eve::as<wide_ft>())   << std::endl
            << "-> inv_egamma[lower](as<wide_ft>())       = " << eve::inv_egamma[eve::lower](eve::as<wide_ft>()) << std::endl;


  std::cout << "---- scalar" << std::endl
            << "-> inv_egamma(as<float>())             = " << eve::inv_egamma(eve::as(float())) << std::endl;


  std::cout << "-> constexpr inv_egamma            = " << constexpr_inv_egamma<float>() << std::endl;

  return 0;
}
