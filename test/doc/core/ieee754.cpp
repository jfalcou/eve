#include <eve/constant/ieee754.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float>;
using wide_it = eve::wide<std::int16_t>;

int main()
{
  wide_ft wxf;
  wide_it wxi;

  std::cout << "---- simd"  << std::endl
            << "-> ieee754(as<wide_ft>())  = " << eve::ieee754(eve::as<wide_ft>()) << std::endl
            << "-> ieee754(as<wide_it>())  = " << eve::ieee754(eve::as<wide_it>()) << std::endl
            << "-> ieee754(as(wxf))        = " << eve::ieee754(eve::as(wxf))       << std::endl
            << "-> ieee754(as(wxi))        = " << eve::ieee754(eve::as(wxi))       << std::endl;

  double       xf;
  std::int16_t xi;

  std::cout << "---- scalar" << std::endl
            << "-> ieee754(as<float>())         = " << eve::ieee754(eve::as(float())) << std::endl
            << "-> ieee754(as<std::int16_t>())  = " << eve::ieee754(eve::as(std::int16_t())) << std::endl
            << "-> ieee754(as<xf))              = " << eve::ieee754(eve::as(xf)) << std::endl
            << "-> ieee754(as<xi))              = " << eve::ieee754(eve::as(xi)) << std::endl;

  return 0;
}
