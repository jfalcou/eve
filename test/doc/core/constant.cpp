#include <eve/constant/constant.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float>;
using wide_it = eve::wide<std::int16_t>;

int main()
{
  wide_ft wxf;
  wide_it wxi;

  std::cout << "---- simd"  << std::endl
            << "-> constant(as<wide_ft>())  = " << eve::constant(eve::as<wide_ft>()) << std::endl
            << "-> constant(as<wide_it>())  = " << eve::constant(eve::as<wide_it>()) << std::endl
            << "-> constant(as(wxf))        = " << eve::constant(eve::as(wxf))       << std::endl
            << "-> constant(as(wxi))        = " << eve::constant(eve::as(wxi))       << std::endl;

  double       xf;
  std::int16_t xi;

  std::cout << "---- scalar" << std::endl
            << "-> constant(as<float>())         = " << eve::constant(eve::as(float())) << std::endl
            << "-> constant(as<std::int16_t>())  = " << eve::constant(eve::as(std::int16_t())) << std::endl
            << "-> constant(as<xf))              = " << eve::constant(eve::as(xf)) << std::endl
            << "-> constant(as<xi))              = " << eve::constant(eve::as(xi)) << std::endl;

  return 0;
}
