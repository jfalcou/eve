#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;

int main()
{

  std::cout << "---- simd"  << std::setprecision(9) << std::endl
            << "-> inv_egamma(as<wide_ft>())                 = " << eve::inv_egamma(eve::as<wide_ft>())                << std::endl
            << "-> upward(inv_egamma)(as<wide_ft>())         = " << eve::upward(eve::inv_egamma)(eve::as<wide_ft>())   << std::endl
            << "-> downward(inv_egamma)(as<wide_ft>())       = " << eve::downward(eve::inv_egamma)(eve::as<wide_ft>()) << std::endl


  std::cout << "---- scalar" << std::endl
            << "-> inv_egamma(as<float>())             = " << eve::inv_egamma(eve::as(float())) << std::endl

  return 0;
}
