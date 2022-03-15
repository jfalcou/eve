#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float>;
using wide_it = eve::wide<std::int16_t>;

int main()
{
  wide_ft wxf;
  wide_it wxi;

  std::cout << "---- simd"  << std::endl
            << "-> true(as<wide_ft>())  = " << eve::true_(eve::as<wide_ft>()) << std::endl
            << "-> true_(as<wide_it>())  = " << eve::true_(eve::as<wide_it>()) << std::endl
            << "-> true_(as(wxf))        = " << eve::true_(eve::as(wxf))       << std::endl
            << "-> true_(as(wxi))        = " << eve::true_(eve::as(wxi))       << std::endl;

  double       xf;
  std::int16_t xi;

  std::cout << "---- scalar" << std::endl
            << "-> true_(as<float>())         = " << eve::true_(eve::as(float())) << std::endl
            << "-> true_(as<std::int16_t>())  = " << eve::true_(eve::as(std::int16_t())) << std::endl
            << "-> true_(as<xf))              = " << eve::true_(eve::as(xf)) << std::endl
            << "-> true_(as<xi))              = " << eve::true_(eve::as(xi)) << std::endl;

  return 0;
}
