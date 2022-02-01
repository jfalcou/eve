#include <eve/module/core/constant/nan.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float>;
using wide_it = eve::wide<std::int16_t>;

int main()
{
  wide_ft wxf;
  wide_it wxi;

  std::cout << "---- simd"  << std::endl
            << "-> nan(as<wide_ft>())  = " << eve::nan(eve::as<wide_ft>()) << std::endl
            << "-> nan(as<wide_it>())  = " << eve::nan(eve::as<wide_it>()) << std::endl
            << "-> nan(as(wxf))        = " << eve::nan(eve::as(wxf))       << std::endl
            << "-> nan(as(wxi))        = " << eve::nan(eve::as(wxi))       << std::endl;

  double       xf;
  std::int16_t xi;

  std::cout << "---- scalar" << std::endl
            << "-> nan(as<float>())         = " << eve::nan(eve::as(float())) << std::endl
            << "-> nan(as<std::int16_t>())  = " << eve::nan(eve::as(std::int16_t())) << std::endl
            << "-> nan(as<xf))              = " << eve::nan(eve::as(xf)) << std::endl
            << "-> nan(as<xi))              = " << eve::nan(eve::as(xi)) << std::endl;

  return 0;
}
