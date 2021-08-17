#include <eve/constant/false.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float>;
using wide_it = eve::wide<std::int16_t>;

int main()
{
  wide_ft wxf;
  wide_it wxi;

  std::cout << "---- simd"  << std::endl
            << "-> false_(as<wide_ft>())  = " << eve::false_(eve::as<wide_ft>()) << std::endl
            << "-> false_(as<wide_it>())  = " << eve::false_(eve::as<wide_it>()) << std::endl
            << "-> false_(as(wxf))        = " << eve::false_(eve::as(wxf))       << std::endl
            << "-> false_(as(wxi))        = " << eve::false_(eve::as(wxi))       << std::endl;

  double       xf;
  std::int16_t xi;

  std::cout << "---- scalar" << std::endl
            << "-> false_(as<float>())         = " << eve::false_(eve::as(float())) << std::endl
            << "-> false_(as<std::int16_t>())  = " << eve::false_(eve::as(std::int16_t())) << std::endl
            << "-> false_(as<xf))              = " << eve::false_(eve::as(xf)) << std::endl
            << "-> false_(as<xi))              = " << eve::false_(eve::as(xi)) << std::endl;

  return 0;
}
