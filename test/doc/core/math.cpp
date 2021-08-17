#include <eve/constant/math.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float>;
using wide_it = eve::wide<std::int16_t>;

int main()
{
  wide_ft wxf;
  wide_it wxi;

  std::cout << "---- simd"  << std::endl
            << "-> math(as<wide_ft>())  = " << eve::math(eve::as<wide_ft>()) << std::endl
            << "-> math(as<wide_it>())  = " << eve::math(eve::as<wide_it>()) << std::endl
            << "-> math(as(wxf))        = " << eve::math(eve::as(wxf))       << std::endl
            << "-> math(as(wxi))        = " << eve::math(eve::as(wxi))       << std::endl;

  double       xf;
  std::int16_t xi;

  std::cout << "---- scalar" << std::endl
            << "-> math(as<float>())         = " << eve::math(eve::as(float())) << std::endl
            << "-> math(as<std::int16_t>())  = " << eve::math(eve::as(std::int16_t())) << std::endl
            << "-> math(as<xf))              = " << eve::math(eve::as(xf)) << std::endl
            << "-> math(as<xi))              = " << eve::math(eve::as(xi)) << std::endl;

  return 0;
}
