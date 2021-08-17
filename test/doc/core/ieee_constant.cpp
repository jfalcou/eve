#include <eve/constant/ieee_constant.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float>;
using wide_it = eve::wide<std::int16_t>;

int main()
{
  wide_ft wxf;
  wide_it wxi;

  std::cout << "---- simd"  << std::endl
            << "-> ieee_constant(as<wide_ft>())  = " << eve::ieee_constant(eve::as<wide_ft>()) << std::endl
            << "-> ieee_constant(as<wide_it>())  = " << eve::ieee_constant(eve::as<wide_it>()) << std::endl
            << "-> ieee_constant(as(wxf))        = " << eve::ieee_constant(eve::as(wxf))       << std::endl
            << "-> ieee_constant(as(wxi))        = " << eve::ieee_constant(eve::as(wxi))       << std::endl;

  double       xf;
  std::int16_t xi;

  std::cout << "---- scalar" << std::endl
            << "-> ieee_constant(as<float>())         = " << eve::ieee_constant(eve::as(float())) << std::endl
            << "-> ieee_constant(as<std::int16_t>())  = " << eve::ieee_constant(eve::as(std::int16_t())) << std::endl
            << "-> ieee_constant(as<xf))              = " << eve::ieee_constant(eve::as(xf)) << std::endl
            << "-> ieee_constant(as<xi))              = " << eve::ieee_constant(eve::as(xi)) << std::endl;

  return 0;
}
