#include <eve/constant/basic.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float>;
using wide_it = eve::wide<std::int16_t>;

int main()
{
  wide_ft wxf;
  wide_it wxi;

  std::cout << "---- simd"  << std::endl
            << "-> basic(as<wide_ft>())  = " << eve::basic(eve::as<wide_ft>()) << std::endl
            << "-> basic(as<wide_it>())  = " << eve::basic(eve::as<wide_it>()) << std::endl
            << "-> basic(as(wxf))        = " << eve::basic(eve::as(wxf))       << std::endl
            << "-> basic(as(wxi))        = " << eve::basic(eve::as(wxi))       << std::endl;

  double       xf;
  std::int16_t xi;

  std::cout << "---- scalar" << std::endl
            << "-> basic(as<float>())         = " << eve::basic(eve::as(float())) << std::endl
            << "-> basic(as<std::int16_t>())  = " << eve::basic(eve::as(std::int16_t())) << std::endl
            << "-> basic(as<xf))              = " << eve::basic(eve::as(xf)) << std::endl
            << "-> basic(as<xi))              = " << eve::basic(eve::as(xi)) << std::endl;

  return 0;
}
